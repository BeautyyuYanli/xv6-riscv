#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int i;

    if (argc != 2)
    {
        write(1, "Require 1 int argument\n", 24);
    }
    else
    {
        sleep(atoi(argv[1]));
    }
    exit(0);
}