#ifndef DIRECTORY_CHECKER_H
#define DIRECTORY_CHECKER_H

#include <stdbool.h>

bool is_path_inside_home(const char *home, const char *requested_path);

#endif

