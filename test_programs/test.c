#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

union opcode {
  uint16_t raw;
  struct {
    uint8_t opcode : 4;
    uint8_t rega   : 4;
    uint8_t regb   : 4;
    uint8_t ctrl   : 4;
  } type_a;
};

int main() {
  FILE *f = fopen("1-chip8-logo.ch8", "rb");
  uint16_t var;
  fread(&var, sizeof(uint16_t), 1, f);
  fread(&var, sizeof(uint16_t), 1, f);

  printf("raw = 0x%04X\n", var);
  printf("raw = 0x%04X\n", (uint16_t)(var << 8));
  printf("raw = 0x%04X\n", (uint16_t)(var >> 8));

  uint16_t raw = (var >> 8) | ( var << 8);

  printf("raw = 0x%04X\n", raw);

  uint8_t *p = (uint8_t*)&raw;

  printf("Address 0: 0x%02X\n", p[0]);
  printf("Address 1: 0x%02X\n", p[1]);

  fclose(f);
  return 0;
}

/*
  fread(&var1, sizeof(uint16_t), 1, f);
  union opcode raw;
  raw.raw = var1;
  uint8_t *p = (uint8_t*)&raw;

  printf("before swap:\n");
  printf("raw = 0x%04X\n", raw.raw);
  printf("Address 0: 0x%02X\n", p[0]);
  printf("Address 1: 0x%02X\n", p[1]);

  printf("raw = 0x%04X\n", raw.raw);
  printf("opcode = 0x%X, rega = 0x%X, regb = 0x%X, ctrl = 0x%X\n",
      raw.type_a.opcode, raw.type_a.rega,
      raw.type_a.regb, raw.type_a.ctrl);

  uint16_t swapped = __builtin_bswap16(var1);
  union opcode raw2;
  raw2.raw = swapped;

  printf("after swap:\n");

  uint8_t *q = (uint8_t*)&raw2.raw;
  printf("Address 0: 0x%02X\n", q[0]);
  printf("Address 1: 0x%02X\n", q[1]);

  printf("raw = 0x%04X\n", raw2.raw);
  printf("opcode = 0x%X, rega = 0x%X, regb = 0x%X, ctrl = 0x%X\n",
      raw2.type_a.opcode, raw2.type_a.rega,
      raw2.type_a.regb, raw2.type_a.ctrl);

*/
