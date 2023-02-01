#ifndef __APPLICATION_H
#define __APPLICATION_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "lib/SDL_FontCache/SDL_FontCache.h"

#include "Vector2D.hpp"


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
            Vector2D<int> graphical = Vector2D<int>();
            Vector2D<double> cartesian = Vector2D<double>();
        } position;

        bool
            left_button_pressed = false,
            is_inside_plot_area = false;

        Vector2D<int> drag_origin_graphical = Vector2D<int>();

        Vector2D<double> drag_origin_cartesian = Vector2D<double>();
    } mouse;

    struct
    {
        Vector2D<double> position = Vector2D<double>();

        Vector2D<double>
            origin_cartesian      = Vector2D<double>(),
            drag_origin_cartesian = Vector2D<double>();

        int range = 1;
    } viewport;

    FC_Font * font = FC_CreateFont();

    void draw ();

    void draw_pointer_coordinates ();
    void draw_plot_area_bounds ();
    void draw_axes ();

    void mouse_button_down (SDL_MouseButtonEvent);
    void mouse_button_up (SDL_MouseButtonEvent);

    void mouse_moved (SDL_MouseMotionEvent);

    void mouse_wheel_scrolled (SDL_MouseWheelEvent);

public:
    Application ();
    ~Application () = default;

    void main_loop ();
};


#endif