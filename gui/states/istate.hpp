#ifndef ISTATE_HPP
#define ISTATE_HPP

#include <utils/noncopiable.hpp>
#include <utils/nonmovable.hpp>

#include <string>

class iState : private utils::noncopiable, private utils::nonmovable
{
public:
    virtual ~iState() = default;

    std::string message() const;

protected:
    iState() = default;

    virtual std::string impl_message() const = 0;
};

#endif // ISTATE_HPP
