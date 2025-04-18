#include "directory_checker.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>

bool is_path_inside_home(const char *home, const char *requested_path)
{
    char home_real[PATH_MAX];
    char path_copy[PATH_MAX];
    char dir_part[PATH_MAX];

    if (!realpath(home, home_real))
        return false;

    // Copy requested path because dirname() can modify it
    strncpy(path_copy, requested_path, sizeof(path_copy));
    path_copy[sizeof(path_copy) - 1] = '\0';

    // Get directory part of the path
    char *dir = dirname(path_copy);

    if (!realpath(dir, dir_part))
        return false; // If the parent folder doesn't exist =reject it 

    size_t len = strlen(home_real);
    return strncmp(home_real, dir_part, len) == 0 &&
           (dir_part[len] == '\0' || dir_part[len] == '/');
}

