#ifndef VILLAGER_HPP
#define VILLAGER_HPP

namespace World
{

class City;

class Villager
{
public:
    enum class State
    {
        Idle,
        Waiting,
        Working
    };

    Villager(const City& city);

    State state() const;

private:
    const City& m_city;
    State m_state = State::Idle;
};

} // World

#endif // VILLAGER_HPP
