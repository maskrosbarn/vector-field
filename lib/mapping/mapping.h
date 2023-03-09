#ifndef MAPPING_H
#define MAPPING_H


#include "Constants/Constants.h"


#ifdef __cplusplus
extern "C" {
#endif

FLOAT_TYPE
graphical_to_cartesian_x (FLOAT_TYPE, FLOAT_TYPE, int);


FLOAT_TYPE
graphical_to_cartesian_y (FLOAT_TYPE, FLOAT_TYPE, int);


FLOAT_TYPE
cartesian_to_graphical_x (FLOAT_TYPE, FLOAT_TYPE, int);


FLOAT_TYPE
cartesian_to_graphical_y (FLOAT_TYPE, FLOAT_TYPE, int);

#ifdef __cplusplus
}
#endif


#endif