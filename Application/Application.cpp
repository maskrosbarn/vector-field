#include <iostream>
#include <algorithm>

#include <SDL2/SDL.h>

#include "Application/Application.hpp"
#include "Constants/Constants.h"
#include "Vector/Vector.h"


void
Application::main ()
{
    SDL_Event event;

    while (is_running)
    {
        while (SDL_PollEvent(&event))
            did_receive_event(event);

        SDL_RenderClear(renderer);

        plot.update();

        particle_engine.draw();
        plot.draw();

        SDL_SetRenderDrawColor(
            renderer,
            BACKGROUND_COLOUR.r,
            BACKGROUND_COLOUR.g,
            BACKGROUND_COLOUR.b,
            BACKGROUND_COLOUR.a
        );

        SDL_RenderPresent(renderer);
    }
}


void
Application::did_receive_event (SDL_Event event)
{
    switch (event.type)
    {
        case SDL_QUIT:
            is_running = false;
            break;

        case SDL_MOUSEMOTION:
            mouse_moved(event.motion);
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouse_button_down(event.button);
            break;

        case SDL_MOUSEBUTTONUP:
            mouse_button_up(event.button);
            break;

        case SDL_MOUSEWHEEL:
            mouse_wheel(event.wheel);
            break;
    }
}


void
Application::mouse_moved (SDL_MouseMotionEvent event)
{
    if (plot.mouse.has_left_button_pressed)
    {
        Vector
            relative_cartesian_mouse_position = vector_graphical_to_cartesian(
                plot.mouse.position.graphical,
                plot.viewport.cartesian_drag_origin,
                plot.viewport.range
            ),
            cartesian_drag_delta = vector_subtract(
                plot.mouse.cartesian_drag_origin,
                relative_cartesian_mouse_position
            );

        plot.viewport.cartesian_origin = vector_add(
            plot.viewport.cartesian_drag_origin,
            cartesian_drag_delta
        );
    }
}


void
Application::mouse_button_down (SDL_MouseButtonEvent event)
{
    switch (event.button)
    {
        case SDL_BUTTON_LEFT:
            plot.mouse.has_left_button_pressed = true;
            plot.mouse.cartesian_drag_origin = plot.mouse.position.cartesian;
            plot.viewport.cartesian_drag_origin = plot.viewport.cartesian_origin;
            break;
    }
}


void
Application::mouse_button_up (SDL_MouseButtonEvent event)
{
    switch (event.button)
    {
        case SDL_BUTTON_LEFT:
            plot.mouse.has_left_button_pressed = false;
            break;
    }
}


void
Application::mouse_wheel (SDL_MouseWheelEvent event)
{
    plot.viewport.range = std::clamp((double)(plot.viewport.range - event.preciseY), 1., 100.);
}


static SDL_Window *
create_window ()
{
    if (SDL_VideoInit(nullptr) < 0)
        throw "[SDL] could not initialise video driver";

    int video_display_count = SDL_GetNumVideoDisplays();

    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(video_display_count - 1, &display_bounds);

    return SDL_CreateWindow(
        "Vector Field",
        display_bounds.x,
        display_bounds.y,
        WINDOW_SIDE_LENGTH,
        WINDOW_SIDE_LENGTH,
        0
    );
}


static SDL_Renderer *
create_renderer (SDL_Window * window)
{
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}


Application::Application (BivariateFunction x, BivariateFunction y):
    window   { create_window() },
    renderer { create_renderer(window) },
    plot (renderer, x, y),
    particle_engine(renderer, plot, x, y)
{
    main();
}


Application::~Application ()
{
    SDL_Quit();
}