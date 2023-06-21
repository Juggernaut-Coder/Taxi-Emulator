#ifndef CLOCK_H
#define CLOCK_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 1920 
#define SCREEN_HEIGHT 1080

SDL_Renderer *renderer;

uint32_t deltaTime = 0;
Uint32 minimum_fps_delta_time = (1000 / 6); //
Uint32 last_game_step ; // initial value
uint32_t last_tick_time = 0;

void tickClock(){
    Uint32 now = SDL_GetTicks();
    // Check so we don't render for no reason, avoid having a 0 delta time
    if (last_game_step < now) {

        Uint32 delta_time = now - last_game_step;

        if (delta_time > minimum_fps_delta_time) {
            delta_time = minimum_fps_delta_time; // slow down if the computer is too slow
        }
        deltaTime = delta_time;
        last_game_step = now;
    }
}
#endif //  CLOCK_H