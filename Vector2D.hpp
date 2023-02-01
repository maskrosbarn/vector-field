#ifndef __Vector2D_H
#define __Vector2D_H


#include <ostream>


template <class T> class Vector2D
{
public:
    T x, y;


    Vector2D (T x = 0, T y = 0):
        x {x},
        y {y}
    {}


    Vector2D<T> operator + (Vector2D<T> operand)
    {
        return Vector2D<T>(x + operand.x, y + operand.y);
    }


    Vector2D<T> operator - (Vector2D<T> operand)
    {
        return Vector2D<T>(x - operand.x, y - operand.y);
    }


    template <class G> Vector2D<T> operator * (G scalar)
    {
        return Vector2D<T>(this->x * scalar, this->y * scalar);
    }


    void operator += (Vector2D<T> operand)
    {
        x += operand.x;
        y += operand.y;
    }


    void operator -= (Vector2D<T> operand)
    {
        x -= operand.x;
        y -= operand.y;
    }
};


template <class T> std::ostream & operator << (std::ostream & out, Vector2D<T> const & vector)
{
    out << "(" << vector.x << ", " << vector.y << ")";
    return out;
}


#endif