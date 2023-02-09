#ifndef __APPLICATION_H
#define __APPLICATION_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Vector2D/Vector2D.hpp"
#include "lib/SDL_FontCache/SDL_FontCache.h"




class Application
{
private:
    SDL_Window * window;
    SDL_Renderer * renderer;

    SDL_Event window_event;

    bool is_running = true;

    struct
    {
        struct
        {
            Vector2D<float>
                graphical = Vector2D<float>(),
                cartesian = Vector2D<float>();
        } position;

        bool
            left_button_pressed = false,
            is_inside_plot_area = false;

        Vector2D<float> drag_origin_graphical = Vector2D<float>();

        Vector2D<float> drag_origin_cartesian = Vector2D<float>();
    } mouse;

    struct
    {
        Vector2D<float> position = Vector2D<float>();

        Vector2D<float>
            origin_cartesian      = Vector2D<float>(),
            drag_origin_cartesian = Vector2D<float>();

        int range = 1;
    } viewport;

    FC_Font * font = FC_CreateFont();

    BivariateFunction gradient_function;
    Vector2D<BivariateFunction> function_vector;

    void (Application:: * draw_method)();


    void initialise ();

    void draw ();

    void draw_pointer_coordinates ();
    void draw_plot_area_bounds ();
    void draw_axes ();
    void draw_slope_field ();

    void draw_vector (Vector2D<float> graphical_position, Vector2D<float> cartesian_position, Vector2D<BivariateFunction> vector);
    void draw_vector_field();

    void mouse_button_down (SDL_MouseButtonEvent);
    void mouse_button_up (SDL_MouseButtonEvent);

    void mouse_moved (SDL_MouseMotionEvent);

    void mouse_wheel_scrolled (SDL_MouseWheelEvent);

public:
    Application ();
    Application (BivariateFunction);
    Application (Vector2D<BivariateFunction>);

    ~Application () = default;

    void main_loop ();
};


#endif