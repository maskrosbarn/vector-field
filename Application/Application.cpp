#include <iostream>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "lib/SDL_FontCache/SDL_FontCache.h"

#include "Application/Application.hpp"
#include "Constants/constants.hpp"




static const int
    WINDOW_SIZE      = 1000,
    WINDOW_SIZE_HALF = WINDOW_SIZE / 2;

static const int
    MOUSE_TEXT_OFFSET = 10;

// SDL window dimensions are measured in whole pixels, so an even window size
// avoids any slight graphical inaccuracies (I think?)
static_assert(WINDOW_SIZE % 2 == 0);

static const int
    PLOT_AREA_INSET = 25,
    PLOT_AREA_SIZE  = WINDOW_SIZE - 2 * PLOT_AREA_INSET;

static const int
    AXES_MAX_POSITION = WINDOW_SIZE - PLOT_AREA_INSET,
    AXES_MIN_POSITION = PLOT_AREA_INSET;




static double
unidimensional_graphical_to_cartesian (int graphical_position, double cartesian_viewport_position, int viewport_range)
{
    double positional_fraction = (double)(graphical_position - WINDOW_SIZE_HALF) / (double)PLOT_AREA_SIZE;

    return positional_fraction * viewport_range + cartesian_viewport_position;
}


static Vector2D<double>
vector_graphical_to_cartesian (Vector2D<int> graphical_position, Vector2D<double> cartesian_viewport_position, int viewport_range)
{
    return Vector2D(
        unidimensional_graphical_to_cartesian(graphical_position.x, cartesian_viewport_position.x, viewport_range),
        unidimensional_graphical_to_cartesian(graphical_position.y, cartesian_viewport_position.y, viewport_range)
    );
}


static int
unidimensional_cartesian_to_graphical (double cartesian_position, double cartesian_viewpoint_position, int viewport_range)
{
    double product = (cartesian_position - cartesian_viewpoint_position) * (double)PLOT_AREA_SIZE;

    return product / (double)viewport_range + WINDOW_SIZE_HALF;
}


static Vector2D<int>
vector_cartesian_to_graphical (Vector2D<double> cartesian_position, Vector2D<double> cartesian_viewport_position, int viewport_range)
{
    return Vector2D(
        unidimensional_cartesian_to_graphical(cartesian_position.x, cartesian_viewport_position.x, viewport_range),
        unidimensional_cartesian_to_graphical(cartesian_position.y, cartesian_viewport_position.y, viewport_range)
    );
}


void Application::draw ()
{
    draw_pointer_coordinates();
    draw_plot_area_bounds();

    draw_axes();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


void Application::draw_pointer_coordinates ()
{
    const char * coordinate_format_string = "(%.1f, %.1f)";

    int
        text_width  = FC_GetWidth(font, coordinate_format_string, mouse.position.cartesian.x, -mouse.position.cartesian.y),
        text_height = FC_GetLineHeight(font),
        text_x      = mouse.position.graphical.x + MOUSE_TEXT_OFFSET,
        text_y      = mouse.position.graphical.y + MOUSE_TEXT_OFFSET;

    if (text_x < AXES_MIN_POSITION)
        text_x = AXES_MIN_POSITION;

    else if (text_x + text_width > AXES_MAX_POSITION)
        text_x = AXES_MAX_POSITION - text_width;

    if (text_y < AXES_MIN_POSITION)
        text_y = AXES_MIN_POSITION;

    else if (text_y + text_height > AXES_MAX_POSITION)
        text_y = AXES_MAX_POSITION - text_height;

    FC_Draw(
        font, 
        renderer, 
        text_x,
        text_y,
        coordinate_format_string,
        mouse.position.cartesian.x,
        -mouse.position.cartesian.y
    );
}


void Application::draw_plot_area_bounds ()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, AXES_MIN_POSITION, AXES_MAX_POSITION, AXES_MIN_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, AXES_MAX_POSITION, AXES_MAX_POSITION, AXES_MAX_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, AXES_MIN_POSITION, AXES_MIN_POSITION, AXES_MAX_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MAX_POSITION, AXES_MIN_POSITION, AXES_MAX_POSITION, AXES_MAX_POSITION);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, WINDOW_SIZE_HALF, 20, WINDOW_SIZE_HALF, AXES_MIN_POSITION);
    SDL_RenderDrawLine(renderer, WINDOW_SIZE_HALF, AXES_MAX_POSITION + 5, WINDOW_SIZE_HALF, AXES_MAX_POSITION);
    SDL_RenderDrawLine(renderer, 20, WINDOW_SIZE_HALF, AXES_MIN_POSITION, WINDOW_SIZE_HALF);
    SDL_RenderDrawLine(renderer, AXES_MAX_POSITION + 5, WINDOW_SIZE_HALF, AXES_MAX_POSITION, WINDOW_SIZE_HALF);
}


void
Application::draw_axes ()
{
    Vector2D<int> axes_position = vector_cartesian_to_graphical(Vector2D<double>(), viewport.origin_cartesian, viewport.range);

    int
        clamped_x_axis_position = std::clamp(axes_position.y, AXES_MIN_POSITION, AXES_MAX_POSITION),
        clamped_y_axis_position = std::clamp(axes_position.x, AXES_MIN_POSITION, AXES_MAX_POSITION);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, clamped_x_axis_position, AXES_MAX_POSITION, clamped_x_axis_position);
    SDL_RenderDrawLine(renderer, clamped_y_axis_position, AXES_MAX_POSITION, clamped_y_axis_position, AXES_MIN_POSITION);

    double
        positive_x_label = viewport.origin_cartesian.x + .5 * viewport.range,
        negative_x_label = viewport.origin_cartesian.x - .5 * viewport.range,
        positive_y_label = viewport.origin_cartesian.y + .5 * viewport.range,
        negative_y_label = viewport.origin_cartesian.y - .5 * viewport.range;

    int positive_label_text_width = FC_GetWidth(font, "%.1f", positive_x_label);

    FC_Draw(font, renderer, AXES_MIN_POSITION, clamped_x_axis_position, "%.1f", negative_x_label);
    FC_Draw(font, renderer, AXES_MAX_POSITION - positive_label_text_width, clamped_x_axis_position, "%.1f", positive_x_label);
}


void
Application::mouse_button_down (SDL_MouseButtonEvent event)
{
    switch (event.button)
    {
        case SDL_BUTTON_LEFT:
            mouse.left_button_pressed = true;
            mouse.drag_origin_cartesian = mouse.position.cartesian;
            viewport.drag_origin_cartesian = viewport.origin_cartesian;
            break;
    }
}


void
Application::mouse_button_up (SDL_MouseButtonEvent event)
{
    switch (event.button)
    {
        case SDL_BUTTON_LEFT:
            mouse.left_button_pressed = false;
            break;
    }
}


void
Application::mouse_moved (SDL_MouseMotionEvent event)
{
    if (mouse.left_button_pressed)
    {
        Vector2D<double>
            relative_mouse_position = vector_graphical_to_cartesian(mouse.position.graphical, viewport.drag_origin_cartesian, viewport.range),
            drag_delta = mouse.drag_origin_cartesian - relative_mouse_position;

        viewport.origin_cartesian = viewport.drag_origin_cartesian + drag_delta;
    }
}


void
Application::mouse_wheel_scrolled (SDL_MouseWheelEvent event)
{
    viewport.range = std::clamp((double)(viewport.range - event.preciseY), 1., 100.);
}


Application::Application ()
{
    if (TTF_Init() < 0)
        throw "[SDL_ttf] failed to initialise";

    SDL_CreateWindowAndRenderer(WINDOW_SIZE, WINDOW_SIZE, 0, &window, &renderer);

    FC_LoadFont(font, renderer, "Monaco.ttf", 12, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);
}


void
Application::main_loop ()
{
    while (is_running)
    {
        while (SDL_PollEvent(&window_event))
        {
            switch (window_event.type)
            {
                case SDL_QUIT:
                    is_running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    Application::mouse_button_down(window_event.button);
                    break;

                case SDL_MOUSEBUTTONUP:
                    Application::mouse_button_up(window_event.button);
                    break;

                case SDL_MOUSEMOTION:
                    Application::mouse_moved(window_event.motion);
                    break;

                case SDL_MOUSEWHEEL:
                    Application::mouse_wheel_scrolled (window_event.wheel);
                    break;
            }
        }

        SDL_GetMouseState(&mouse.position.graphical.x, &mouse.position.graphical.y);

        mouse.is_inside_plot_area =
            (unsigned)(mouse.position.graphical.x - AXES_MIN_POSITION) <= PLOT_AREA_SIZE &&
            (unsigned)(mouse.position.graphical.y - AXES_MIN_POSITION) <= PLOT_AREA_SIZE;

        mouse.position.cartesian.x = unidimensional_graphical_to_cartesian(
            mouse.position.graphical.x,
            viewport.origin_cartesian.x,
            viewport.range
        );

        mouse.position.cartesian.y = unidimensional_graphical_to_cartesian(
            mouse.position.graphical.y,
            viewport.origin_cartesian.y,
            viewport.range
        );

        SDL_RenderClear(renderer);

        this->draw();

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
}