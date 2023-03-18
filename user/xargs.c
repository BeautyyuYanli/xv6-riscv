#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
int read_argv(char (*argv)[MAXPATH])
// return -1 if EOF
//        argc else
{
    int argc = 0, s = 0;
    for (char *arg = argv[argc++]; 1; arg = argv[argc++])
    {
        char t;
        int c = 0, f = 0;
        while ((s = read(0, &t, 1)) == 1)
        {
            if (t == ' ')
                if (f == 0)
                    continue;
                else
                    break;
            else if (t == '\n')
                break;
            else
                arg[c++] = t, f = 1;
        }
        arg[c] = 0;
        if (s != 1 || t == '\n')
            break;
    }
    return (argc == 1 && argv[0][0] == '\0' && s != 1) ? -1 : argc;
}
int main(int argc, char **argv)
{

    static char argv_new[MAXARG][MAXPATH];
    char *argv_exe[MAXARG];

    while (1)
    {

        int argc_new = read_argv(argv_new);
        if (argc_new == -1)
            break;
        for (int i = 0; i < argc; ++i)
            argv_exe[i] = argv[i];
        for (int i = 0; i < argc_new; ++i)
            argv_exe[i + argc] = argv_new[i];

        if (fork() == 0)
            exec(argv_exe[1], argv_exe + 1);
        else
            wait(0);
    }
    exit(0);
}