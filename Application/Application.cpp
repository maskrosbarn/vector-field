#include <iostream>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Application/Application.hpp"
#include "Constants.hpp"
#include "lib/SDL_FontCache/SDL_FontCache.h"
#include "lib/mapping/mapping.hpp"
#include "Bivariate/Bivariate.hpp"




void
Application::draw ()
{
    draw_pointer_coordinates();
    draw_plot_area_bounds();

    draw_axes();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


void
Application::draw_pointer_coordinates ()
{
    const char * coordinate_format_string = "(%.1f, %.1f)";

    int
        text_width  = FC_GetWidth(font, coordinate_format_string, mouse.position.cartesian.x, mouse.position.cartesian.y),
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
        mouse.position.cartesian.y
    );
}


void
Application::draw_plot_area_bounds ()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, AXES_MIN_POSITION, AXES_MAX_POSITION, AXES_MIN_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, AXES_MAX_POSITION, AXES_MAX_POSITION, AXES_MAX_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, AXES_MIN_POSITION, AXES_MIN_POSITION, AXES_MAX_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MAX_POSITION, AXES_MIN_POSITION, AXES_MAX_POSITION, AXES_MAX_POSITION);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, WINDOW_SIZE_HALF, AXES_MIN_POSITION - 5, WINDOW_SIZE_HALF, AXES_MIN_POSITION);
    SDL_RenderDrawLine(renderer, WINDOW_SIZE_HALF, AXES_MAX_POSITION + 5, WINDOW_SIZE_HALF, AXES_MAX_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION - 5, WINDOW_SIZE_HALF, AXES_MIN_POSITION, WINDOW_SIZE_HALF);
    SDL_RenderDrawLine(renderer, AXES_MAX_POSITION + 5, WINDOW_SIZE_HALF, AXES_MAX_POSITION, WINDOW_SIZE_HALF);
}


void
Application::draw_axes ()
{
    Vector2D<int> axes_position = vector_cartesian_to_graphical(Vector2D<double>(), viewport.origin_cartesian, viewport.range);

    int
        x_axis_position = std::clamp(axes_position.y, AXES_MIN_POSITION, AXES_MAX_POSITION),
        y_axis_position = std::clamp(axes_position.x, AXES_MIN_POSITION, AXES_MAX_POSITION);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, x_axis_position, AXES_MAX_POSITION, x_axis_position);
    SDL_RenderDrawLine(renderer, y_axis_position, AXES_MAX_POSITION, y_axis_position, AXES_MIN_POSITION);

    double
        positive_x_label = viewport.origin_cartesian.x + .5 * viewport.range,
        negative_x_label = viewport.origin_cartesian.x - .5 * viewport.range,
        positive_y_label = viewport.origin_cartesian.y + .5 * viewport.range,
        negative_y_label = viewport.origin_cartesian.y - .5 * viewport.range;

    const char * format = "%.1f";

    int
        axis_label_height           = FC_GetLineHeight(font),
        positive_x_label_text_width = FC_GetWidth(font, format, positive_x_label),
        negative_x_label_text_width = FC_GetWidth(font, format, negative_x_label),
        positive_y_label_text_width = FC_GetWidth(font, format, positive_y_label),
        negative_y_label_text_width = FC_GetWidth(font, format, negative_y_label);

    int
        x_axis_label_position          = x_axis_position,
        positive_y_axis_label_position = y_axis_position,
        negative_y_axis_label_position = y_axis_position;

    if (x_axis_position <= AXES_MIN_POSITION + 50)
        x_axis_label_position = AXES_MIN_POSITION - axis_label_height;
    
    else if (x_axis_position >= AXES_MAX_POSITION - 50)
        x_axis_label_position = AXES_MAX_POSITION + 1;

    if (y_axis_position <= AXES_MIN_POSITION + 50)
    {
        positive_y_axis_label_position = AXES_MIN_POSITION - positive_y_label_text_width - 2;
        negative_y_axis_label_position = AXES_MIN_POSITION - negative_y_label_text_width - 2;
    }
    else if (y_axis_position >= AXES_MAX_POSITION - 50)
    {
        positive_y_axis_label_position = AXES_MAX_POSITION + 2;
        negative_y_axis_label_position = AXES_MAX_POSITION + 2;
    }

    FC_Draw(font, renderer, AXES_MIN_POSITION, x_axis_label_position, format, negative_x_label);
    FC_Draw(font, renderer, AXES_MAX_POSITION - positive_x_label_text_width, x_axis_label_position, format, positive_x_label);

    FC_Draw(font, renderer, positive_y_axis_label_position, AXES_MIN_POSITION, format, positive_y_label);
    FC_Draw(font, renderer, negative_y_axis_label_position, AXES_MAX_POSITION - axis_label_height, format, negative_y_label);
}


static void
draw_gradient_vector (SDL_Renderer * renderer, Vector2D<int> position, double gradient)
{
    //
}


void
Application::draw_vector_field ()
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

    for (;;)
    {
        //
    }
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
            drag_delta              = mouse.drag_origin_cartesian - relative_mouse_position;

        viewport.origin_cartesian = viewport.drag_origin_cartesian + drag_delta;
    }
}


void
Application::mouse_wheel_scrolled (SDL_MouseWheelEvent event)
{
    viewport.range = std::clamp((double)(viewport.range - event.preciseY), 1., 100.);
}


Application::Application (Bivariate::Expression * gradient_expression):
    gradient_expression {gradient_expression}
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

        mouse.position.cartesian.x = graphical_to_cartesian_x(
            mouse.position.graphical.x,
            viewport.origin_cartesian.x,
            viewport.range
        );

        mouse.position.cartesian.y = graphical_to_cartesian_y(
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