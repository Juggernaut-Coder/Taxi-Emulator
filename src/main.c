#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Clock.h"
#include "Game.h"
#include "Utils/vector.h"
#include <time.h>
#include <SDL2/SDL_ttf.h>


int init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    IMG_Init(IMG_INIT_PNG);
    if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return -1;
	}
    font = TTF_OpenFont("images/font.ttf", 16);
    //another lib init here

    return 0;
}

int main(int argc, char** argv){
    (void)argc;(void)argv;
    if(init() == 1){ //init
        return 1;
    }    
    srand(time(NULL));
    SDL_Window *window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    last_game_step = SDL_GetTicks();
    gameStart();

    int running = 1;
    while(running == 1){
        tickClock();

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    printf("\t"); // print clicked positioni
                    Vec2i pos = newVec2(event.button.x, event.button.y);
                    Vec2i v = getRowColFromPos(33,60,pos);
                    printf("clicked row col: %d %d \n",v.y, v.x);
                    onMapClick(pos.x,pos.y);
                    break;
                case SDL_KEYDOWN:
                    printf("KEY PRESS : %d\n", event.key.keysym.sym);
                    onKeyClick(event.key.keysym.sym);
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        gameDraw();
        gameUpdate();
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}

