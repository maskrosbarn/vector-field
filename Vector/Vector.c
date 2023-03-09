#include <math.h>

#include "Vector/Vector.h"
#include "Constants/Constants.h"
#include "lib/mapping/mapping.h"


Vector make_vector
(
    FLOAT_TYPE x,
    FLOAT_TYPE y
)
{
    Vector vector;
    vector.x = x;
    vector.y = y;

    return vector;
}


Vector
vector_add (Vector lhs, Vector rhs)
{
    return make_vector(lhs.x + rhs.x, lhs.y + rhs.y);
}


Vector
vector_subtract (Vector lhs, Vector rhs)
{
    return make_vector(lhs.x - rhs.x, lhs.y - rhs.y);
}


Vector
vector_scalar_multiply (FLOAT_TYPE scalar, Vector vector)
{
    return make_vector(scalar * vector.x, scalar * vector.y);
}


FLOAT_TYPE
vector_magnitude (Vector vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}


FLOAT_TYPE
vector_angle (Vector vector)
{
    float angle = acos(vector.x / vector_magnitude(vector));

    return vector.y > 0 ? angle : TWO_PI - angle;
}


Vector
vector_normalised (Vector vector)
{
    FLOAT_TYPE magnitude = vector_magnitude(vector);

    if (magnitude == 0)
        return make_vector(0, 0);

    FLOAT_TYPE fraction = 1 / magnitude;

    return make_vector(fraction * vector.x, fraction * vector.y);
}


Vector
vector_graphical_to_cartesian
(
    Vector graphical_position,
    Vector cartesian_viewport_position,
    int    viewport_range
)
{
    Vector cartesian_position;

    cartesian_position.x = graphical_to_cartesian_x(
        graphical_position.x,
        cartesian_viewport_position.x,
        viewport_range
    );

    cartesian_position.y = graphical_to_cartesian_y(
        graphical_position.y,
        cartesian_viewport_position.y,
        viewport_range
    );

    return cartesian_position;
}

Vector
vector_cartesian_to_graphical
(
    Vector cartesian_position,
    Vector cartesian_viewport_position,
    int    viewport_range
)
{
    Vector graphical_position;

    graphical_position.x = cartesian_to_graphical_x(
        cartesian_position.x,
        cartesian_viewport_position.x,
        viewport_range
    );

    graphical_position.y = cartesian_to_graphical_y(
        cartesian_position.y,
        cartesian_viewport_position.y,
        viewport_range
    );

    return graphical_position;
}