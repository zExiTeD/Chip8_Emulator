#include "./opcode.c"
#include "./system.h"
#include <time.h>


struct system InitializeSystem( File_t file ) {
    struct system system = { 0 };

    memcpy( &system.memory[512] , file.data , file.size );
    system.cpu.program_counter = 0x200; // 0x200 == 512
    memcpy(system.memory, FontSet, sizeof(FontSet));

    CreateOpcodeTable( &system );

    return system;
}

void Execute(struct system* System) {
    struct opcode op_code = opcode_get(System);
    uint16_t old_pc = System->cpu.program_counter;

    System->op_hashmap[op_code.Group].exec(System, op_code);

    if (System->cpu.program_counter == old_pc) {
        System->cpu.program_counter += 2;
    }
    srand((unsigned int)time(NULL));
}
