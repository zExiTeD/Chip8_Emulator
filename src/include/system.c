#include "./system.h"
#include "./allocator.h"
#include "./helper.h"

void
system_initialize(struct system* system, struct allocator* allocator, file_t file) {

}

op_code
op_code_get(struct system* system) {
  return 0;
}

void
system_execute_opcode(struct system* system) {
  op_code opcode = op_code_get(system);
}

void system_check_collision(struct system* system) {
}

void system_display_draw(struct system* system) {
}
