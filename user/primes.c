#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p1[2], p2[2];
    int *pp1 = p1, *pp2 = p2;
    int main_f = 1, end_f = 0;
    int base;

    pipe(pp1);
    while (fork() == 0)
    {
        main_f = 0;
        close(pp1[1]);
        // Consume a number
        pipe(pp2);
        if (read(pp1[0], &base, 4) == 4)
        {
            printf("prime %d\n", base);
        }
        else
        {
            end_f = 1;
            break;
        }

        // Swap for the next process
        int *pp_tmp = pp1;
        pp1 = pp2;
        pp2 = pp_tmp;
    }
    if (main_f == 1)
    {
        close(pp1[0]);
        for (int i = 2; i <= 35; ++i)
        {
            write(pp1[1], &i, 4);
        }
        close(pp1[1]);
        wait(0);
    }
    else
    {
        // Swap back for the current process
        int *pp_tmp = pp1;
        pp1 = pp2;
        pp2 = pp_tmp;
        close(pp2[0]);
        // Pass the unsieved numbers
        int value;
        while (read(pp1[0], &value, 4) == 4)
        {
            if (value % base != 0)
            {
                write(pp2[1], &value, 4);
            }
        }
        close(pp1[0]);
        close(pp2[1]);
        if (end_f == 0)
            wait(0);
    }
    exit(0);
}