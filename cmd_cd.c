#include "cmd_cd.h"
#include "directory_checker"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int handle_cd(int sock, const char *home, char *cwd,
              const char *arg_line)
{
    if (!arg_line || !*arg_line)
        arg_line = home;                 

    char dest[PATH_MAX];
    snprintf(dest, sizeof(dest), "%s/%s", cwd, arg_line);

    if (!path_is_inside_home(home, dest))
        return send(sock, "Reject access\n", 14, 0);

    // changing working dir to dest if it exist. 
    if (chdir(dest) == -1)
        return send(sock, "Directory not found\n", 20, 0);
	
    // update the cwd ,so the server knows the clint is in new location. 
    if (!getcwd(cwd, PATH_MAX))
        perror("getcwd");       
    return 0;
}

