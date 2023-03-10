#ifndef CONSTANTS_H
#define CONSTANTS_H


#include <stdlib.h>


#ifdef GPU_ACCELERATION
    #include <OpenCL/opencl.h>
    #define FLOAT_TYPE cl_float
#else
    #define FLOAT_TYPE float
#endif

#include <SDL2/SDL.h>

#define TWO_PI 6.28318530717958647692528676655900576

extern const int RAND_MAX_HALF;

#define WINDOW_SIDE_LENGTH         1000.f
extern const FLOAT_TYPE WINDOW_SIDE_LENGTH_HALF;

#define PLOT_AREA_INSET            50.f
extern const FLOAT_TYPE PLOT_AREA_SIDE_LENGTH;

extern const FLOAT_TYPE
    AXES_MAX_POSITION,
    AXES_MIN_POSITION;

extern const SDL_Colour
    BACKGROUND_COLOUR,
    FOREGROUND_COLOUR;

#define FONT_FILE_NAME             "Monaco.ttf"
#define FONT_SIZE                  11

#define MOUSE_TEXT_OFFSET          20

#define VECTOR_ROW_COUNT           30
#define VECTOR_COLUMN_COUNT        30
#define VECTOR_LENGTH              38
#define VECTOR_HEAD_LENGTH         12
extern const int VECTOR_COUNT;
extern const FLOAT_TYPE VECTOR_LENGTH_HALF;

enum Vector_Properties
{
    MAGNITUDE,

    TAIL_X, TAIL_Y,

    HEAD_X, HEAD_Y,

    LEFT_X, LEFT_Y,

    RIGHT_X, RIGHT_Y,

    TIP_X, TIP_Y,

    COLOUR_R, COLOUR_G, COLOUR_B,

    VECTOR_PROPERTY_COUNT
};

#define PARTICLE_SIZE 4.f
extern const FLOAT_TYPE PARTICLE_SIZE_HALF;

#define PARTICLE_COUNT 3000

enum Particle_Properties
{
    VISIBLE,

    STATE,

    POSITION_X, POSITION_Y,

    PARTICLE_PROPERTY_COUNT
};

enum Particle_Visibility
{
    NO, YES
};

enum Particle_State
{
    NEW, OLD
};


#endif