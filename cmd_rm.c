#include "cmd_rm.h"
#include "directory_checker.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int handle_rm(int sock, const char *home, const char *cwd,
              const char *arg_line)
{
    if (!arg_line || !*arg_line)
        return send(sock, "rm missing arugemnt\n", 20, 0);

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", cwd, arg_line);

    if (!path_is_inside_home(home, path))
        return send(sock, "Reject access\n", 14, 0);

    if (remove(path) == -1)
        return send(sock, "rm cannot remove\n", 17, 0);

    return 0;
}

