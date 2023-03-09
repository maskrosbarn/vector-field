#include <stdlib.h>
#include <iostream>

#include "lib/misc_functions/functions.hpp"


float
random_between (float maximum, float minimum)
{
    float normalised_random = rand() / (float)RAND_MAX;

    return normalised_random * (maximum - minimum) + minimum;
}