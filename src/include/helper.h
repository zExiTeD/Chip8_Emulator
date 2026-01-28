#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdint.h>
#include "./allocator.h"

typedef struct {
  FILE      *file_descriptor;
  uint32_t  file_size;
  uint8_t   *file_data;
} file_t;

static uint32_t be_to_le32(uint32_t x) { return __builtin_bswap32(x); }
static uint16_t be_to_le16(uint16_t x) { return __builtin_bswap16(x); }

static file_t
open_and_read_entire_file(const char* file_path, struct allocator* allocator) {
  file_t file;
  file.file_descriptor = fopen(file_path, "r");

  fseek(file.file_descriptor, 0, SEEK_END);
  file.file_size = (uint32_t)ftell(file.file_descriptor);
  fseek(file.file_descriptor, 0, SEEK_SET);

  file.file_data = allocator->alloc(allocator, file.file_size);
  size_t read_bytes = fread(file.file_data, 1, file.file_size, file.file_descriptor);
  (void)read_bytes;

  return file;
}

#endif
