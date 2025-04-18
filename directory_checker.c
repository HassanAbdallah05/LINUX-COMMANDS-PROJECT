#include "directory_checker.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

bool is_path_inside_home(const char *home, const char *requested_path)
{
    char home_real[PATH_MAX];
    char dir_part[PATH_MAX];
    char real_dir_path[PATH_MAX]; 

    if (!realpath(home, home_real))
        return false;

    // Extract the dir part of requested path [manually]. 
    const char *last_slash = strrchr(requested_path, '/');
    if (!last_slash) {
        // If there is no slash this means current directory.
        strcpy(dir_part, ".");
    } else {
        size_t len = last_slash - requested_path;
        if (len >= sizeof(dir_part))
            len = sizeof(dir_part) - 1;
        strncpy(dir_part, requested_path, len);
        dir_part[len] = '\0';
    }

    // the real path of the directory
    if (!realpath(dir_part, real_dir_path))
        return false;

    size_t len = strlen(home_real);
    return strncmp(home_real, real_dir_path, len) == 0 &&
           (real_dir_path[len] == '\0' || real_dir_path[len] == '/');
}
