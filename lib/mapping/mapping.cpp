#include "Constants.hpp"
#include "Vector2D.hpp"




double
graphical_to_cartesian_x (int graphical_position, double cartesian_viewport_position, int viewport_range)
{
    double positional_fraction = (double)(graphical_position - WINDOW_SIZE_HALF) / (double)PLOT_AREA_SIZE;

    return positional_fraction * viewport_range + cartesian_viewport_position;
}


double
graphical_to_cartesian_y (int graphical_position, double cartesian_viewport_position, int viewport_range)
{
    double positional_fraction = (double)(WINDOW_SIZE_HALF - graphical_position) / (double)PLOT_AREA_SIZE;

    return positional_fraction * viewport_range + cartesian_viewport_position;
}


Vector2D<double>
vector_graphical_to_cartesian (Vector2D<int> graphical_position, Vector2D<double> cartesian_viewport_position, int viewport_range)
{
    return Vector2D(
        graphical_to_cartesian_x(graphical_position.x, cartesian_viewport_position.x, viewport_range),
        graphical_to_cartesian_y(graphical_position.y, cartesian_viewport_position.y, viewport_range)
    );
}


int
cartesian_to_graphical_x (double cartesian_position, double cartesian_viewpoint_position, int viewport_range)
{
    double product = (cartesian_position - cartesian_viewpoint_position) * (double)PLOT_AREA_SIZE;

    return product / (double)viewport_range + WINDOW_SIZE_HALF;
}


int
cartesian_to_graphical_y (double cartesian_position, double cartesian_viewpoint_position, int viewport_range)
{
    double product = (cartesian_position - cartesian_viewpoint_position) * (double)PLOT_AREA_SIZE;

    return WINDOW_SIZE_HALF - product / (double)viewport_range;
}


Vector2D<int>
vector_cartesian_to_graphical (Vector2D<double> cartesian_position, Vector2D<double> cartesian_viewport_position, int viewport_range)
{
    return Vector2D(
        cartesian_to_graphical_x(cartesian_position.x, cartesian_viewport_position.x, viewport_range),
        cartesian_to_graphical_y(cartesian_position.y, cartesian_viewport_position.y, viewport_range)
    );
}