#include <stdlib.h>
//
#include <iostream>

#include "Application/Application.hpp"
#include "Constants/Constants.h"
#include "lib/BivariateFunction.h"
#include "lib/misc_functions/functions.hpp"


int main (int argc, char const * argv[])
{
    srand(time(nullptr));

    system("clear");
    
    BivariateFunction
        x = [](Vector position) -> FLOAT_TYPE { return position.y; },
        y = [](Vector position) -> FLOAT_TYPE { return -.2 * position.y - (9.8 / 8) * sin(position.x); };

    Application application(x, y);

    return 0;
}
