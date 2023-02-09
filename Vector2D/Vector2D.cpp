#include <math.h>

#include "Vector2D/Vector2D.hpp"




float
magnitude (Vector2D<BivariateFunction> vector, Vector2D<float> position)
{
    return sqrt(pow(vector.x(position), 2) + pow(vector.y(position), 2));
}


Vector2D<float>
resolve (Vector2D<BivariateFunction> vector, Vector2D<float> cartesian_position)
{
    return Vector2D(vector.x(cartesian_position), vector.y(cartesian_position));
}