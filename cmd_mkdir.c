#include "cmd_mkdir.h"
#include "directory_checker.h"
#include <sys/stat.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int handle_mkdir(int sock, const char *home, const char *cwd,
                 const char *arg_line)
{
    if (!arg_line || !*arg_line)
        return send(sock, "mkdir missing argument\n", 23, 0);

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", cwd, arg_line);

    if (!path_is_inside_home(home, path))
        return send(sock, "Reject access\n", 14, 0);

    if (mkdir(path, 0755) == -1)
        return send(sock, "mkdir cannot create\n", 20, 0);

    return 0;
}

