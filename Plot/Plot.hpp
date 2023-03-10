#ifndef PLOT_H
#define PLOT_H


#include <SDL2/SDL.h>

#include "Constants/Constants.h"
#include "Vector/Vector.h"
#include "lib/BivariateFunction.h"
#include "lib/SDL_FontCache/SDL_FontCache.h"


class Plot
{
private:
    SDL_Renderer * renderer;

    FC_Font * font = FC_CreateFont();

    BivariateFunction x_function, y_function;

    FLOAT_TYPE vector_properties_matrix[VECTOR_ROW_COUNT][VECTOR_COLUMN_COUNT][VECTOR_PROPERTY_COUNT];


    void update_vector_property_matrix ();

    void draw_plot_bounds () const;
    void draw_axes () const;
    void draw_axes_labels () const;
    void draw_pointer_coordinates () const;

    void draw_vector_field () const;
    void draw_vector (size_t, size_t) const;


public:
    struct
    {
        struct
        {
            Vector
                graphical = { 0, 0 },
                cartesian = { 0, 0 };
        } position;

        Vector cartesian_drag_origin = { 0, 0 };

        bool
            has_left_button_pressed = false,
            is_inside_plot_area     = false;
        
    } mouse;

    struct
    {
        Vector
            cartesian_origin      = { 0, 0 },
            cartesian_drag_origin = { 0, 0 };

        Vector
            axes_maximum = { .5f, .5f },
            axes_minimum = { -.5f, -.5f };

        int range = 1;
    } viewport;

    Vector axes_position = { 0, 0 };


    Plot (SDL_Renderer *, BivariateFunction, BivariateFunction);

    void update ();

    void draw () const;

    Vector get_direction_vector (Vector) const;

    Vector cartesian_to_graphical (Vector) const;
    Vector graphical_to_cartesian (Vector) const;

    Vector fixed_graphical_length_from_cartesian (Vector, FLOAT_TYPE, FLOAT_TYPE) const;

    static bool is_inside_plot_area (Vector);
    bool is_inside_viewport_area (Vector) const;
};


#endif