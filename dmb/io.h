#ifndef DMB_IO
#define DMB_IO

#include <stdbool.h>
#include "./vec.h"

bool is_space(char c);

char *strip(char *s);

Vec *IO_read_input(char *pathname);

#endif
