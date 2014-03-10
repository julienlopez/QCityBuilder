#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <utils/deep_ptr.hpp>
#include <utils/noncopiable.hpp>
#include <utils/nonmovable.hpp>

using namespace ::testing;

using deep_ptr_int = utils::deep_ptr<int>;

TEST(TestDeepPtrDefaut, TestDefaultConstructor)
{
    deep_ptr_int p;
    ASSERT_FALSE(p);
}

TEST(TestDeepPtrDefaut, TestInstanciation)
{
    deep_ptr_int p(new int(23));
    ASSERT_TRUE(p);
    ASSERT_EQ(23, *p);
}

TEST(TestDeepPtrDefaut, CopyOfAnEmptyPointer)
{
    deep_ptr_int p1;
    deep_ptr_int p2 = p1;
    ASSERT_FALSE(p2);
}

TEST(TestDeepPtrDefaut, TestCopy)
{
    deep_ptr_int p(new int(23));
    deep_ptr_int p2(p);
    ASSERT_EQ(23, *p2);
    ASSERT_NE(p, p2);
}

TEST(TestDeepPtrDefaut, TestCopiedInstanceIsIndependant)
{
    deep_ptr_int p(new int(23));
    deep_ptr_int p2(p);

    *p2 = 1;

    ASSERT_EQ(1, *p2);
    ASSERT_EQ(23, *p);
}

struct TestDeepPtrWithClonePolicy : public ::testing::Test
{
    class Base : private utils::noncopiable, private utils::nonmovable
    {
    public:
        virtual ~Base() = default;

        virtual Base* clone() const =0;

        virtual bool operator ==(const Base& b) const = 0;

        virtual void aMethod() const = 0;

    protected:
        Base() {}
    };

    class MockBase : public Base
    {
    public:
        MOCK_CONST_METHOD0(clone, Base*());
        MOCK_CONST_METHOD0(aMethod, void());

        MockBase(int i): m_i(i)
        {
            ON_CALL(*this, clone()).WillByDefault(Invoke(this, &MockBase::impl_clone));
        }

        MockBase(const MockBase& bm):Base(), m_i(bm.m_i) {}

    private:
        int m_i;

        Base* impl_clone() const //TODO move to private if possible
        {
            return new MockBase(*this);
        }

        virtual bool operator ==(const Base& b) const override
        {
            auto* mb = dynamic_cast<const MockBase*>(&b);
            assert(mb);
            return m_i == mb->m_i;
        }

        void impl_aMethod() const {}
    };

    using deep_ptr_base = utils::deep_ptr<Base, utils::deep_ptr_clone_copy>;
};

TEST_F(TestDeepPtrWithClonePolicy, TestCopy)
{
    auto* mockbase = new MockBase(25);
    deep_ptr_base p1(mockbase);
    EXPECT_CALL(*mockbase, clone()).Times(1);
    deep_ptr_base p2(p1);
    ASSERT_EQ(*p1, *p2);
    ASSERT_NE(p1, p2);
}

TEST_F(TestDeepPtrWithClonePolicy, TestMethodCall)
{
    auto* mockbase = new MockBase(25);
    deep_ptr_base p1(mockbase);

    EXPECT_CALL(*mockbase, aMethod()).Times(1);
    p1->aMethod();

    EXPECT_CALL(*mockbase, clone()).Times(1);
    auto p2 = p1;

    auto* mockbase2 = dynamic_cast<MockBase*>(p2.get());
    EXPECT_CALL(*mockbase2, aMethod()).Times(1);
    p2->aMethod();
}
