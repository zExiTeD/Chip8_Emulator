#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stdlib.h>

#include "./helper.h"

#define CHIP8_SCREEN_WIDTH 64
#define CHIP8_SCREEN_HEIGHT 32

typedef uint16_t op_code;

struct cpu {
  uint8_t   V[16];
  uint8_t   sp;
  uint16_t  program_counter;
  uint16_t  I;
};

struct system {
  /* 
0x000-0x1FF : Original interpreter ROM 
0x200       : program entry point
0xEA0-0xEFF : reserved
0xF00-0xFFF : Display mem, Ignored
*/
  uint8_t     memory[4096];
  uint16_t    stack[16];
  struct cpu  cpu;
  uint8_t     sound_timer;
  uint8_t     delay_timer;
  uint8_t     display[CHIP8_SCREEN_WIDTH * CHIP8_SCREEN_HEIGHT];
};

void system_initialize(struct system* system, struct allocator* allocator, file_t file);
void system_execute_opcode(struct system* system);
void system_display_draw(struct system* system);
void system_check_collision(struct system* system);

#endif
