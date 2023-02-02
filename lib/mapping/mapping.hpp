#include "Vector2D.hpp"




double
graphical_to_cartesian_x (int graphical_position, double cartesian_viewport_position, int viewport_range);


double
graphical_to_cartesian_y (int graphical_position, double cartesian_viewport_position, int viewport_range);


Vector2D<double>
vector_graphical_to_cartesian (Vector2D<int> graphical_position, Vector2D<double> cartesian_viewport_position, int viewport_range);


int
cartesian_to_graphical_x (double cartesian_position, double cartesian_viewpoint_position, int viewport_range);


int
cartesian_to_graphical_y (double cartesian_position, double cartesian_viewpoint_position, int viewport_range);


Vector2D<int>
vector_cartesian_to_graphical (Vector2D<double> cartesian_position, Vector2D<double> cartesian_viewport_position, int viewport_range);