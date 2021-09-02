#ifndef COORDINATE_POINT_HPP
#define COORDINATE_POINT_HPP

struct CoordinatePoint{
    float x;
    float y;
    float rad;

    CoordinatePoint operator+(CoordinatePoint other) const{
        return {
                x + other.x,
                y + other.y,
                rad + other.rad
        };
    };
    CoordinatePoint operator-(CoordinatePoint other) const{
        return {
                x - other.x,
                y - other.y,
                rad - other.rad
        };
    };
};

#endif // COORDINATE_POINT_HPP
