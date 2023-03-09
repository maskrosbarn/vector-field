#ifndef APPLICATION_H
#define APPLICATION_H
//#define GPU_ACCELERATION

#include <SDL2/SDL.h>

#ifdef GPU_ACCELERATION
    #include <OpenCL/opencl.hpp>
#endif

#include "Constants/Constants.h"
#include "lib/BivariateFunction.h"
#include "Plot/Plot.hpp"
#include "ParticleEngine/ParticleEngine.hpp"


class Application
{
private:
    bool is_running = true;

    SDL_Window * window;

    SDL_Renderer * renderer;

    Plot plot;

    ParticleEngine particle_engine;

    void main ();

    void did_receive_event (SDL_Event);

    void mouse_moved (SDL_MouseMotionEvent);
    void mouse_button_down (SDL_MouseButtonEvent);
    void mouse_button_up (SDL_MouseButtonEvent);
    void mouse_wheel (SDL_MouseWheelEvent);

public:
    Application (BivariateFunction, BivariateFunction);

    ~Application ();
};


#endif