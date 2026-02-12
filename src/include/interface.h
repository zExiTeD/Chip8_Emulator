#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL.h>
#include <stdio.h>

#include "./system.h"

struct SDL_state {
    SDL_Window      *Window;
    SDL_Renderer    *Renderer;
    SDL_Event       Event;
    Uint8           Running;
};

struct SDL_state SDL_CreateState( int width, int height, char* title) {
    struct SDL_state state = { 0 };

    SDL_Init(SDL_INIT_VIDEO);
    state.Window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        ( SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE ) );

    if( state.Window == NULL ) {
        printf(" [ ERROR ] : Failed to Create Window ");
    }

    state.Renderer = SDL_CreateRenderer(state.Window, -1, SDL_RENDERER_ACCELERATED);

    state.Running = 1;

    return state;
}

void SystemToSDLWindowMapper( struct system* system, struct SDL_state* state){
    SDL_Renderer* renderer = state->Renderer;

    int scale_factor = 10;

    for (int y = 0; y < CHIP8_SCREEN_HEIGHT; y++) {
      for (int x = 0; x < CHIP8_SCREEN_WIDTH; x++) {
        int index = y * CHIP8_SCREEN_WIDTH + x;

        if (system->display[index]) {
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        } else {
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }

        SDL_Rect rect = {
          x * scale_factor,
          y * scale_factor,
          scale_factor,
          scale_factor
        };
        SDL_RenderFillRect(renderer, &rect);
      }
    }
}

void SDLToSystemKYB( struct system* system, struct SDL_state* state ){

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    system->keyboard[0x1] = keys[SDL_SCANCODE_1];  // 1
    system->keyboard[0x2] = keys[SDL_SCANCODE_2];  // 2
    system->keyboard[0x3] = keys[SDL_SCANCODE_3];  // 3
    system->keyboard[0xC] = keys[SDL_SCANCODE_4];  // C

    system->keyboard[0x4] = keys[SDL_SCANCODE_Q];  // 4
    system->keyboard[0x5] = keys[SDL_SCANCODE_W];  // 5
    system->keyboard[0x6] = keys[SDL_SCANCODE_E];  // 6
    system->keyboard[0xD] = keys[SDL_SCANCODE_R];  // D

    system->keyboard[0x7] = keys[SDL_SCANCODE_A];  // 7
    system->keyboard[0x8] = keys[SDL_SCANCODE_S];  // 8
    system->keyboard[0x9] = keys[SDL_SCANCODE_D];  // 9
    system->keyboard[0xE] = keys[SDL_SCANCODE_F];  // E

    system->keyboard[0xA] = keys[SDL_SCANCODE_Z];  // A
    system->keyboard[0x0] = keys[SDL_SCANCODE_X];  // 0
    system->keyboard[0xB] = keys[SDL_SCANCODE_C];  // B
    system->keyboard[0xF] = keys[SDL_SCANCODE_V];  // F
}


#endif
