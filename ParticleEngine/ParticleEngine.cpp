#include <stdlib.h>
#include <iostream>

#include "ParticleEngine/ParticleEngine.hpp"
#include "lib/misc_functions/functions.hpp"


void
ParticleEngine::draw_particle (Vector cartesian_position) const
{
    Vector graphical_position = plot.cartesian_to_graphical(cartesian_position);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

    SDL_FRect rect {
        graphical_position.x - PARTICLE_SIZE_HALF,
        graphical_position.y - PARTICLE_SIZE_HALF,
        PARTICLE_SIZE,
        PARTICLE_SIZE
    };

    SDL_RenderFillRectF(renderer, &rect);
}


void
ParticleEngine::update ()
{
    FLOAT_TYPE * properties;

    Vector
        cartesian_position,
        dt,
        next_position;

    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        properties = particle_properties[i];

        properties[VISIBLE] = YES;
        properties[STATE] = OLD;

        cartesian_position = { properties[POSITION_X], properties[POSITION_Y] };

        if (properties[STATE] == OLD && !plot.is_inside_viewport_area(cartesian_position))
        {
            properties[VISIBLE] = NO;
            properties[STATE] = NEW;
            
            next_position = get_new_position();
        }
        else
        {
            dt = { plot_x_function(cartesian_position), plot_y_function(cartesian_position) };

            if (vector_magnitude(dt) < .55)
            {
                properties[VISIBLE] = NO;
                properties[STATE] = NEW;
            
                next_position = get_new_position();
            }
            else
            {
                next_position = get_next_position(cartesian_position);

                if (properties[STATE] == NEW && !plot.is_inside_viewport_area(next_position))
                {
                    properties[VISIBLE] = NO;
                    //properties[STATE] = OLD;

                    next_position = get_new_position();
                }
            }
        }

        particle_properties[i][POSITION_X] = next_position.x;
        particle_properties[i][POSITION_Y] = next_position.y;

        //printf("%d %.3f %.3f\n", properties[STATE] < .001 ? 0 : 1, properties[POSITION_X], properties[POSITION_Y]);
    }

    //printf("\x1B[%iA", PARTICLE_COUNT);
}


Vector
ParticleEngine::get_new_position () const
{
    FLOAT_TYPE position;

    bool
        vertical_orientation_flag = rand() > RAND_MAX_HALF,
        max_side_flag = rand() > RAND_MAX_HALF;

    if (vertical_orientation_flag)
    {
        position = random_between(plot.viewport.axes_maximum.x, plot.viewport.axes_minimum.x);

        return {
            position,
            max_side_flag ? plot.viewport.axes_maximum.y : plot.viewport.axes_minimum.y
        };
    }

    position = random_between(plot.viewport.axes_maximum.y, plot.viewport.axes_minimum.y);

    return {
        max_side_flag ? plot.viewport.axes_maximum.x : plot.viewport.axes_minimum.x,
        position
    };
}


Vector
ParticleEngine::get_next_position (Vector current_cartesian_position) const
{
    Vector change = {
        plot_x_function(current_cartesian_position),
        plot_y_function(current_cartesian_position)
    };

    return vector_add(
        current_cartesian_position,
        vector_scalar_multiply(.01, vector_normalised(change))
    );
}


ParticleEngine::ParticleEngine
(
    SDL_Renderer *    renderer,
    const Plot &      plot,
    BivariateFunction x_function,
    BivariateFunction y_function
):
    renderer { renderer },
    plot { plot },
    plot_x_function { x_function },
    plot_y_function { y_function }
{
    Vector position;

    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        position = get_new_position();

        particle_properties[i][POSITION_X] = position.x;
        particle_properties[i][POSITION_Y] = position.y;

        //for (i = POSITION_X; i < PARTICLE_PROPERTY_COUNT; i++)
        //    particle_properties[j][i] = ;
    }

    //memset(particle_properties, 2, PARTICLE_COUNT * PARTICLE_PROPERTY_COUNT * sizeof(FLOAT_TYPE));
}


void
ParticleEngine::start_drawing ()
{
    should_draw = true;
}


void
ParticleEngine::stop_drawing ()
{
    should_draw = false;
}


void
ParticleEngine::draw ()
{
    //if (!should_draw)
    //    return;

    update();

    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        if (particle_properties[i][VISIBLE] == YES)
            draw_particle({ particle_properties[i][POSITION_X], particle_properties[i][POSITION_Y] });
    }
}