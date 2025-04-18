#include "cmd_touch.h"
#include "directory_checker.h"
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int handle_touch(int sock, const char *home, const char *cwd,
                 const char *arg_line)
{
    if (!arg_line || !*arg_line)
        return send(sock, "touch missing argument\n", 23, 0);

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", cwd, arg_line);

    if (!path_is_inside_home(home, path))
        return send(sock, "Reject access\n", 14, 0);

    int fd = open(path, O_CREAT | O_WRONLY, 0644);
    if (fd == -1)
        return send(sock, "touch cannot create\n", 20, 0);

    close(fd);
    return 0;
}

