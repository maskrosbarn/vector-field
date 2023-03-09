#include <iostream>
#include <algorithm>
#include <math.h>

#include "Plot/Plot.hpp"
#include "Constants/Constants.h"


void
Plot::update ()
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    mouse.position.graphical = { (FLOAT_TYPE)mouse_x, (FLOAT_TYPE)mouse_y };

    mouse.position.cartesian = vector_graphical_to_cartesian(
        mouse.position.graphical,
        viewport.cartesian_origin,
        viewport.range
    );

    mouse.is_inside_plot_area = is_inside_plot_area(mouse.position.graphical);

    Vector axes_position = cartesian_to_graphical({ 0, 0 });

    this->axes_position = {
        std::clamp(axes_position.y, AXES_MIN_POSITION, AXES_MAX_POSITION),
        std::clamp(axes_position.x, AXES_MIN_POSITION, AXES_MAX_POSITION)
    };

    float half_viewport_range = viewport.range / 2;

    viewport.axes_maximum = {
        viewport.cartesian_origin.x + half_viewport_range,
        viewport.cartesian_origin.y + half_viewport_range
    };

    viewport.axes_minimum = {
        viewport.cartesian_origin.x - half_viewport_range,
        viewport.cartesian_origin.y - half_viewport_range
    };

    update_vector_property_matrix();
}


void
Plot::update_vector_property_matrix ()
{
    Vector
        graphical_tail_position,
        cartesian_tail_position;

    Vector
        cartesian_direction,
        graphical_head_position,
        cartesian_head_position;

    Vector
        arrow_left_graphical_position,
        arrow_right_graphical_position,
        arrow_tip_graphical_position;

    FLOAT_TYPE
        direction_magnitude,
        direction_angle;

    FLOAT_TYPE
        magnitude_colour_mapping,
        colour_red,
        colour_green,
        colour_blue;

    for (size_t property_id, i, j = 0; j < VECTOR_ROW_COUNT; j++)
    {
        for (i = 0; i < VECTOR_COLUMN_COUNT; i++)
        {
            graphical_tail_position = {
                (2 * i + 1) * PLOT_AREA_SIDE_LENGTH / (2 * VECTOR_ROW_COUNT) + PLOT_AREA_INSET,
                (2 * j + 1) * PLOT_AREA_SIDE_LENGTH / (2 * VECTOR_COLUMN_COUNT) + PLOT_AREA_INSET
            };

            cartesian_tail_position = graphical_to_cartesian(graphical_tail_position);

            cartesian_direction = {
                x_function(cartesian_tail_position),
                y_function(cartesian_tail_position)
            };

            direction_magnitude = vector_magnitude(cartesian_direction);

            vector_properties_matrix[j][i][MAGNITUDE] = direction_magnitude;

            if (direction_magnitude > 0)
            {
                direction_angle = vector_angle(cartesian_direction);

                graphical_head_position = fixed_graphical_length_from_cartesian(
                    cartesian_tail_position,
                    VECTOR_LENGTH_HALF - VECTOR_HEAD_LENGTH,
                    direction_angle
                );

                cartesian_head_position = graphical_to_cartesian(graphical_head_position);

                arrow_left_graphical_position = fixed_graphical_length_from_cartesian(
                    cartesian_head_position,
                    6,
                    direction_angle - M_PI_4
                );

                arrow_right_graphical_position = fixed_graphical_length_from_cartesian(
                    cartesian_head_position,
                    6,
                    direction_angle + M_PI_4
                );

                arrow_tip_graphical_position = fixed_graphical_length_from_cartesian(
                    cartesian_head_position,
                    VECTOR_HEAD_LENGTH,
                    direction_angle
                );

                magnitude_colour_mapping = 1 - 5 / (direction_magnitude + 5);

                colour_red = 55 + 200 * magnitude_colour_mapping;
                colour_green = 0;
                colour_blue = 55 + 200 * (1 - magnitude_colour_mapping);

                FLOAT_TYPE properties [] = {
                    direction_magnitude,

                    graphical_tail_position.x, graphical_tail_position.y,

                    graphical_head_position.x, graphical_head_position.y,

                    arrow_left_graphical_position.x, arrow_left_graphical_position.y,
                    arrow_right_graphical_position.x, arrow_right_graphical_position.y,
                    arrow_tip_graphical_position.x, arrow_tip_graphical_position.y,

                    colour_red, colour_green, colour_blue
                };

                for (property_id = TAIL_X; property_id < VECTOR_PROPERTY_COUNT; property_id++)
                    vector_properties_matrix[j][i][property_id] = properties[property_id];
            }
        }
    }
}


void
Plot::draw_plot_bounds () const
{
    SDL_SetRenderDrawColor(renderer, FOREGROUND_COLOUR.r, FOREGROUND_COLOUR.g, FOREGROUND_COLOUR.b, FOREGROUND_COLOUR.a);

    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, AXES_MIN_POSITION, AXES_MAX_POSITION, AXES_MIN_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, AXES_MAX_POSITION, AXES_MAX_POSITION, AXES_MAX_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, AXES_MIN_POSITION, AXES_MIN_POSITION, AXES_MAX_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MAX_POSITION, AXES_MIN_POSITION, AXES_MAX_POSITION, AXES_MAX_POSITION);

    SDL_RenderDrawLine(renderer, WINDOW_SIDE_LENGTH_HALF, AXES_MIN_POSITION - 5, WINDOW_SIDE_LENGTH_HALF, AXES_MIN_POSITION);
    SDL_RenderDrawLine(renderer, WINDOW_SIDE_LENGTH_HALF, AXES_MAX_POSITION + 5, WINDOW_SIDE_LENGTH_HALF, AXES_MAX_POSITION);
    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION - 5, WINDOW_SIDE_LENGTH_HALF, AXES_MIN_POSITION, WINDOW_SIDE_LENGTH_HALF);
    SDL_RenderDrawLine(renderer, AXES_MAX_POSITION + 5, WINDOW_SIDE_LENGTH_HALF, AXES_MAX_POSITION, WINDOW_SIDE_LENGTH_HALF);
}


void
Plot::draw_axes () const
{
    SDL_SetRenderDrawColor(renderer, FOREGROUND_COLOUR.r, FOREGROUND_COLOUR.g, FOREGROUND_COLOUR.b, FOREGROUND_COLOUR.a);

    SDL_RenderDrawLine(renderer, AXES_MIN_POSITION, this->axes_position.x, AXES_MAX_POSITION, this->axes_position.x);
    SDL_RenderDrawLine(renderer, this->axes_position.y, AXES_MAX_POSITION, this->axes_position.y, AXES_MIN_POSITION);
}


void
Plot::draw_axes_labels () const
{
    double
        positive_x_label = viewport.cartesian_origin.x + .5 * viewport.range,
        negative_x_label = viewport.cartesian_origin.x - .5 * viewport.range,
        positive_y_label = viewport.cartesian_origin.y + .5 * viewport.range,
        negative_y_label = viewport.cartesian_origin.y - .5 * viewport.range;

    const char * format = "%.1f";

    int
        axis_label_height           = FC_GetLineHeight(font),
        positive_x_label_text_width = FC_GetWidth(font, format, positive_x_label),
        negative_x_label_text_width = FC_GetWidth(font, format, negative_x_label),
        positive_y_label_text_width = FC_GetWidth(font, format, positive_y_label),
        negative_y_label_text_width = FC_GetWidth(font, format, negative_y_label);

    int
        x_axis_label_position          = axes_position.x,
        positive_y_axis_label_position = axes_position.y,
        negative_y_axis_label_position = axes_position.y;

    if (axes_position.x <= AXES_MIN_POSITION + 50)
        x_axis_label_position = AXES_MIN_POSITION - axis_label_height;
    
    else if (axes_position.x >= AXES_MAX_POSITION - 50)
        x_axis_label_position = AXES_MAX_POSITION + 1;

    if (axes_position.y <= AXES_MIN_POSITION + 50)
    {
        positive_y_axis_label_position = AXES_MIN_POSITION - positive_y_label_text_width - 2;
        negative_y_axis_label_position = AXES_MIN_POSITION - negative_y_label_text_width - 2;
    }
    else if (axes_position.y >= AXES_MAX_POSITION - 50)
    {
        positive_y_axis_label_position = AXES_MAX_POSITION + 2;
        negative_y_axis_label_position = AXES_MAX_POSITION + 2;
    }

    FC_Draw(font, renderer, AXES_MIN_POSITION, x_axis_label_position, format, negative_x_label);
    FC_Draw(font, renderer, AXES_MAX_POSITION - positive_x_label_text_width, x_axis_label_position, format, positive_x_label);

    FC_Draw(font, renderer, positive_y_axis_label_position, AXES_MIN_POSITION, format, positive_y_label);
    FC_Draw(font, renderer, negative_y_axis_label_position, AXES_MAX_POSITION - axis_label_height, format, negative_y_label);
}


void
Plot::draw_pointer_coordinates () const
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
Plot::draw_vector_field () const
{
    SDL_SetRenderDrawColor(
        renderer,
        FOREGROUND_COLOUR.r,
        FOREGROUND_COLOUR.g,
        FOREGROUND_COLOUR.b,
        FOREGROUND_COLOUR.a
    );

    for (size_t i, j = 0; j < VECTOR_ROW_COUNT; j++)
    {
        for (i = 0; i < VECTOR_COLUMN_COUNT; i++)
            draw_vector(i, j);
    }
}


void
Plot::draw_vector (size_t i, size_t j) const
{
    SDL_Colour colour {
        (Uint8)vector_properties_matrix[j][i][COLOUR_R],
        (Uint8)vector_properties_matrix[j][i][COLOUR_G],
        (Uint8)vector_properties_matrix[j][i][COLOUR_B]
    };

    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);

    SDL_RenderDrawLineF(
        renderer,
        vector_properties_matrix[j][i][TAIL_X],
        vector_properties_matrix[j][i][TAIL_Y],
        vector_properties_matrix[j][i][HEAD_X],
        vector_properties_matrix[j][i][HEAD_Y]
    );

    SDL_Vertex vertices [] = {
        {
            { vector_properties_matrix[j][i][HEAD_X], vector_properties_matrix[j][i][HEAD_Y] },
            colour,
            { 0 }
        },
        {
            { vector_properties_matrix[j][i][LEFT_X], vector_properties_matrix[j][i][LEFT_Y] },
            colour,
            { 0 }
        },
        {
            { vector_properties_matrix[j][i][RIGHT_X], vector_properties_matrix[j][i][RIGHT_Y] },
            colour,
            { 0 }
        },
        {
            { vector_properties_matrix[j][i][TIP_X], vector_properties_matrix[j][i][TIP_Y] },
            colour,
            { 0 }
        },
    };

    int indices [] = { 0, 1, 2, 1, 2, 3 };

    SDL_RenderGeometry(renderer, nullptr, vertices, 4, indices, 6);
}


Plot::Plot
(
    SDL_Renderer *    renderer,
    BivariateFunction x_function,
    BivariateFunction y_function
):
    renderer   { renderer },
    x_function { x_function },
    y_function { y_function }
{
    FC_LoadFont(
        font,
        renderer,
        FONT_FILE_NAME,
        FONT_SIZE,
        { FOREGROUND_COLOUR.r, FOREGROUND_COLOUR.g, FOREGROUND_COLOUR.b, FOREGROUND_COLOUR.a },
        TTF_STYLE_NORMAL
    );

    update_vector_property_matrix();
}


void
Plot::draw () const
{
    draw_plot_bounds();
    draw_axes();
    draw_axes_labels();

    if (mouse.is_inside_plot_area)
        draw_pointer_coordinates();

    draw_vector_field();
}


Vector
Plot::get_direction_vector (Vector position) const
{
    return { x_function(position), y_function(position) };
}


Vector
Plot::cartesian_to_graphical (Vector position) const
{
    return vector_cartesian_to_graphical(position, viewport.cartesian_origin, viewport.range);
}


Vector
Plot::graphical_to_cartesian (Vector position) const
{
    return vector_graphical_to_cartesian(position, viewport.cartesian_origin, viewport.range);
}


Vector
Plot::fixed_graphical_length_from_cartesian
(
    Vector     cartesian_position,
    FLOAT_TYPE graphical_length,
    FLOAT_TYPE angle
) const
{
    Vector
        graphical_position = cartesian_to_graphical(cartesian_position),
        adjustment         = vector_scalar_multiply(graphical_length, { cos(-angle), sin(-angle) });

    return vector_add(graphical_position, adjustment);
}


static bool
is_in_range (int value, int minimum, int maximum)
{
    return (unsigned)(value - minimum) <= (maximum + minimum);
}


bool
Plot::is_inside_plot_area (Vector vector)
{
    return
        is_in_range(vector.x, AXES_MIN_POSITION, AXES_MAX_POSITION) &&
        is_in_range(vector.y, AXES_MIN_POSITION, AXES_MAX_POSITION);
}


bool
Plot::is_inside_viewport_area (Vector vector) const
{
    float half_range = .5 * viewport.range;

    return
        is_in_range(vector.x, viewport.axes_minimum.x, viewport.axes_maximum.x) &&
        is_in_range(vector.y, viewport.axes_minimum.y, viewport.axes_maximum.y);
}