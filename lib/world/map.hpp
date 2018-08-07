#ifndef MAP_HPP
#define MAP_HPP

#include "namespace_world.hpp"

#include <utils/array2d.hpp>
#include <utils/rect.hpp>

BEGIN_NAMESPACE_WORLD

class Map
{
public:
    enum class SquareType : unsigned char
    {
        Empty = 0,
        Building,
        Road
    };

    using square_container_t = std::vector<utils::PointU>;

    Map(utils::SizeU size_);

    std::size_t width() const;
    std::size_t height() const;

    const utils::SizeU& size() const;

    bool squareIsEmpty(const utils::PointU& p) const;

    void placeBuilding(const utils::RectU& r);

    SquareType squareType(const utils::PointU& p) const;

    void addRoad(square_container_t squares);

private:
    using type_container = utils::Array2D<SquareType>;
    type_container m_squares;
};

END_NAMESPACE_WORLD

#endif // MAP_HPP
