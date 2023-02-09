#include <iostream>
#include <math.h>

#include <SDL2/SDL.h>

#include "Vector2D/Vector2D.hpp"
#include "Application/Application.hpp"




int main (int argc, char const * argv[])
{
    BivariateFunction
        x = [](Vector2D<float> position) -> float { return position.y; },
        y = [](Vector2D<float> position) -> float { return -.2 * position.y - (9.8 / 8) * sin(position.x); };

    Vector2D<BivariateFunction> pendulum_equation_vector = Vector2D(x, y);

    Application application(pendulum_equation_vector);
    application.main_loop();

    return 0;
}