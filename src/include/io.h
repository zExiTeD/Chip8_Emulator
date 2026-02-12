#ifndef IO_H
#define IO_H

#include <stdio.h>

typedef struct {
    FILE    *fd;
    int     size;
    char    data[ ( 4096 - 512 ) ];
} File_t;


static File_t open_and_read_entire_file(const char *file_path) {
  File_t file;
  fopen_s(&file.fd, file_path, "rb");

  fseek(file.fd, 0, SEEK_END);
  file.size = ftell(file.fd);
  fseek(file.fd, 0, SEEK_SET);

  if (file.size > (4096 - 512)) {
    printf("[ ERROR ] : Rom Size is greater than Chip8 Memory \n");
    fclose(file.fd);
  }

  size_t read_bytes = fread(&file.data, 1, file.size, file.fd);

  if (!(read_bytes == file.size)) {
    printf("[ ERROR ] : Failed to read to memory \n");
    fclose(file.fd);
  }

  fclose(file.fd);
  return file;
}

#endif
