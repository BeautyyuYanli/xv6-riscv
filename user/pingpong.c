#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2];
    int t;
    pipe(p);
    if (fork() == 0)
    {
        close(p[0]);
        read(p[1], &t, 1);
        printf("%d: received ping\n", getpid());
        write(p[1], " ", 1);
        close(p[1]);
    }
    else
    {
        close(p[1]);
        write(p[0], " ", 1);
        read(p[0], &t, 1);
        printf("%d: received pong\n", getpid());
        close(p[0]);
    }

    exit(0);
}
