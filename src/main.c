#include "./include/interface.h"
#include "./include/system.h"
#include "./include/system.c"
#include "./include/io.h"

int
main( int argc, char* argv[]){

    if( argc < 2 ){
        printf("Usage ./exe <filename> \n");
        return 0;
    }

    printf("%s \n", argv[1]);
    File_t file = open_and_read_entire_file(argv[1]);

    struct SDL_state state =  SDL_CreateState(800,600,"- Chip8 -");
    struct system   system = InitializeSystem( file );

    Uint32 last_cycle_time = SDL_GetTicks();
    Uint32 last_timer_time = SDL_GetTicks();
    const float cycle_delay = 1000.0f / 700.0f;
    const float timer_delay = 1000.0f / 120.0f;


    while( state.Running  ) {
       while( SDL_PollEvent(&state.Event) ) {
           if (state.Event.type == SDL_QUIT) {
             state.Running = 0;
           }
       }

       SDLToSystemKYB( &system , &state );
       SystemToSDLWindowMapper(&system , &state);

       Uint32 current_time = SDL_GetTicks();
       if (current_time - last_cycle_time >= cycle_delay) {
           Execute(&system);
           last_cycle_time = current_time;
       }

       // Update timers at 60Hz
       if (current_time - last_timer_time >= timer_delay) {
           if (system.delay_timer > 0) system.delay_timer--;
           if (system.sound_timer > 0) system.sound_timer--;
           last_timer_time = current_time;
       }

       SDL_RenderPresent(state.Renderer);
    }

    return 0;
}
