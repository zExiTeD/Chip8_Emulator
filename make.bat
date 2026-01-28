:: cl /I C:\Users\yadu\Projects\chip8\vendor\sdl2-compat-devel-2.32.62-VC\sdl2-compat-2.32.62\include ^
:: src\main.c /link /LIBPATH:C:\Users\yadu\Projects\chip8\vendor\sdl2-compat-devel-2.32.62-VC\sdl2-compat-2.32.62\lib\x64 SDL2.lib /Fe:build\main.exe

clang .\src\main.c ^
-D SDL_MAIN_HANDLED ^
-L .\vendor\sdl2-compat-devel-2.32.62-VC\sdl2-compat-2.32.62\lib\x64\ ^
-I .\vendor\sdl2-compat-devel-2.32.62-VC\sdl2-compat-2.32.62\include ^
-lSDL2 ^
-o build\main.exe
