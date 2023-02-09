#include <iostream>
#include <algorithm>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Application/Application.hpp"
#include "Constants.hpp"
#include "Vector2D/Vector2D.hpp"
#include "lib/SDL_FontCache/SDL_FontCache.h"
#include "lib/mapping/mapping.hpp"




void
Application::initialise ()
{
    if (TTF_Init() < 0)
        throw "[SDL_ttf] failed to initialise";

    SDL_CreateWindowAndRenderer(WINDOW_SIZE, WINDOW_SIZE, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Slope Field");

    FC_LoadFont(font, renderer, "Monaco.ttf", 14, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);
}


void
Application::draw ()
{
    ((*this).*draw_method)();

    draw_axes();
    draw_pointer_coordinates();
    draw_plot_area_bounds();

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
    Vector2D<float> axes_position = vector_cartesian_to_graphical(Vector2D<float>(), viewport.origin_cartesian, viewport.range);

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
draw_slope_line (SDL_Renderer * renderer, Vector2D<float> position, double gradient)
{
    double angle = atan(-gradient);

    SDL_RenderDrawLineF(
        renderer,
        position.x + VECTOR_LENGTH_HALF * cos(angle),
        position.y + VECTOR_LENGTH_HALF * sin(angle),
        position.x + VECTOR_LENGTH_HALF * -cos(angle),
        position.y + VECTOR_LENGTH_HALF * -sin(angle)
    );
}


void
Application::draw_slope_field ()
{
    SDL_SetRenderDrawColor(renderer, 165, 165, 165, 255);

    Vector2D<float> graphical_position, cartesian_position;

    for (int i = 0; i != VECTOR_FIELD_COUNT; i++)
    {
        graphical_position = Vector2D(
            (i % VECTOR_FIELD_DENSITY) * VECTOR_WIDTH + PLOT_AREA_INSET + VECTOR_WIDTH_HALF,
            (i / VECTOR_FIELD_DENSITY) * VECTOR_WIDTH + PLOT_AREA_INSET + VECTOR_WIDTH_HALF
        );

        cartesian_position = vector_graphical_to_cartesian(graphical_position, viewport.origin_cartesian, viewport.range);

        draw_slope_line(renderer, graphical_position, gradient_function(cartesian_position));
    }
}


/*static void
draw_triangle (SDL_Renderer * renderer, )
{
    //
}*/


void
Application::draw_vector (Vector2D<float> graphical_position, Vector2D<float> cartesian_position_vector, Vector2D<BivariateFunction> vector)
{
    float positional_magnitude = magnitude(vector, cartesian_position_vector);

    if (positional_magnitude == 0)
    {
        return;
    }

    float magnitude_colour_constant = 1 - 5 / (5 + positional_magnitude);

    Vector2D<float>
        cartesian_normalised_direction_vector = resolve(vector, cartesian_position_vector) * (1 / positional_magnitude),
        graphical_normalised_direction_vector = vector_cartesian_to_graphical(
            cartesian_position_vector + cartesian_normalised_direction_vector,
            viewport.origin_cartesian,
            viewport.range
        ),
        relative_graphical_normalised_direction_vector = graphical_position + graphical_normalised_direction_vector;

    SDL_SetRenderDrawColor(
        renderer,
        55 + 200 * magnitude_colour_constant,
        0,
        55 + 200 * (1 - magnitude_colour_constant),
        255
    );

    SDL_RenderDrawLineF(
        renderer,
        graphical_position.x,
        graphical_position.y,
        graphical_normalised_direction_vector.x,
        graphical_normalised_direction_vector.y
    );
}


void
Application::draw_vector_field ()
{
    Vector2D<float> vector_graphical_position, vector_cartesian_position;

    for (int i = 0; i != VECTOR_FIELD_COUNT; i++)
    {
        vector_graphical_position = Vector2D(
            (i % VECTOR_FIELD_DENSITY) * VECTOR_WIDTH + PLOT_AREA_INSET + VECTOR_WIDTH_HALF,
            (i / VECTOR_FIELD_DENSITY) * VECTOR_WIDTH + PLOT_AREA_INSET + VECTOR_WIDTH_HALF
        );

        vector_cartesian_position = vector_graphical_to_cartesian(vector_graphical_position, viewport.origin_cartesian, viewport.range);

        draw_vector(vector_graphical_position, vector_cartesian_position, function_vector);
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
        Vector2D<float>
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


Application::Application (BivariateFunction gradient_function):
    gradient_function {gradient_function}
{
    initialise();

    draw_method = &Application::draw_slope_field;
}


Application::Application (Vector2D<BivariateFunction> function_vector):
    function_vector {function_vector}
{
    initialise();

    draw_method = &Application::draw_vector_field;
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

        int mouse_x, mouse_y;

        SDL_GetMouseState(&mouse_x, &mouse_y);
        mouse.position.graphical = Vector2D((float)mouse_x, (float)mouse_y);

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