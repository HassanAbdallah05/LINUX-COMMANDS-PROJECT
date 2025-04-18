#include "cmd_ls.h"
#include "directory_checker.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int handle_ls(int sock, const char *home, const char *cwd,
              const char *arg_line)
{
    char target[PATH_MAX];
  
    // checks if the arg_line is not empty append it to cwd to build the target path.
    // else if arg_line is empty/null use (cwd). 
    if (arg_line && *arg_line)
        snprintf(target, sizeof(target), "%s/%s", cwd, arg_line);
    else
        strncpy(target, cwd, sizeof(target));



    // ensure the target_path within the user home dir. 
    if (!path_is_inside_home(home, target))
        return send(sock, "Reject access\n", 14, 0);

    DIR *dp = opendir(target);
    if (!dp)
        return send(sock, "Cannot open directory\n", 22, 0);


    // read (each file/folder) from the target directroy and print it in newline
    // format.  
    struct dirent *de;
    char line[1024];
    while ((de = readdir(dp)))
    {
        int n = snprintf(line, sizeof(line), "%s\n", de->d_name);
        send(sock, line, n, 0);
    }

    closedir(dp);
    return 0;
}

