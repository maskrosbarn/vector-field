#ifndef PARTICLE_ENGINE_H
#define PARTICLE_ENGINE_H


#include <SDL2/SDL.h>

#include "lib/BivariateFunction.h"
#include "Vector/Vector.h"
#include "Plot/Plot.hpp"


class ParticleEngine
{
private:
    SDL_Renderer * renderer;

    const Plot & plot;

    BivariateFunction
        plot_x_function,
        plot_y_function;

    bool should_draw = true;

    FLOAT_TYPE particle_properties[PARTICLE_COUNT][PARTICLE_PROPERTY_COUNT];


    void draw_particle (Vector) const;

    void update ();
    Vector get_new_position () const;
    Vector get_next_position (Vector) const;

public:
    ParticleEngine
    (
        SDL_Renderer *,
        const Plot &,
        BivariateFunction,
        BivariateFunction
    );

    void start_drawing ();
    void stop_drawing ();

    void draw ();
};


#endif