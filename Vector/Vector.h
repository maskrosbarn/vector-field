#ifndef VECTOR_H
#define VECTOR_H


#include "Constants/Constants.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct Vector
{
    FLOAT_TYPE x, y;
} Vector;


Vector make_vector (FLOAT_TYPE, FLOAT_TYPE);


Vector vector_add (Vector, Vector);

Vector vector_subtract (Vector, Vector);

Vector vector_scalar_multiply (FLOAT_TYPE, Vector);

FLOAT_TYPE vector_magnitude (Vector);

FLOAT_TYPE vector_angle (Vector);

Vector vector_normalised (Vector);

Vector vector_graphical_to_cartesian (Vector, Vector, int);

Vector vector_cartesian_to_graphical (Vector, Vector, int);

#ifdef __cplusplus
}
#endif


#endif