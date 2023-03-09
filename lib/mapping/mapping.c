#include "lib/mapping/mapping.h"
#include "Constants/Constants.h"


FLOAT_TYPE
graphical_to_cartesian_x
(
    FLOAT_TYPE position,
    FLOAT_TYPE cartesian_viewport_position,
    int        viewport_range
)
{
    FLOAT_TYPE
        a = (FLOAT_TYPE)viewport_range / PLOT_AREA_SIDE_LENGTH,
        b = position - WINDOW_SIDE_LENGTH_HALF;

    return a * b + cartesian_viewport_position;
}


FLOAT_TYPE
graphical_to_cartesian_y
(
    FLOAT_TYPE position,
    FLOAT_TYPE cartesian_viewport_position,
    int        viewport_range
)
{
    FLOAT_TYPE
        a = (FLOAT_TYPE)viewport_range / PLOT_AREA_SIDE_LENGTH,
        b = WINDOW_SIDE_LENGTH_HALF - position;

    return a * b + cartesian_viewport_position;
}


FLOAT_TYPE
cartesian_to_graphical_x
(
    FLOAT_TYPE position,
    FLOAT_TYPE cartesian_viewport_position,
    int        viewport_range
)
{
    FLOAT_TYPE a = PLOT_AREA_SIDE_LENGTH * (position - cartesian_viewport_position);

    return WINDOW_SIDE_LENGTH_HALF + a / (FLOAT_TYPE)viewport_range;
}


FLOAT_TYPE
cartesian_to_graphical_y
(
    FLOAT_TYPE position,
    FLOAT_TYPE cartesian_viewport_position,
    int        viewport_range
)
{
    FLOAT_TYPE a = PLOT_AREA_SIDE_LENGTH * (position - cartesian_viewport_position);

    return WINDOW_SIDE_LENGTH_HALF - a / (FLOAT_TYPE)viewport_range;
}