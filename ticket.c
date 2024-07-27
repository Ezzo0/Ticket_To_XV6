#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"


int
main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(1, "Error, input should be one argument\n");
        exit();
    }
    

    printf(1, "test_Ticket\n");

    int number = atoi(argv[1]);
    int ret = settickets(number);

    if (ret == -1)
    {
        printf(1, "Failed to set process' tickets\n");
        exit();
    }

    // int i = 0;

    // for (i = 0; i < 10; i++)
    // {
    //     printf(1, "running process: %d\n", getpid);
    // }
    
    
    while (1)
    {
        /* code */
        /* just for delay */
    }

    exit(); // eq to return zero
}
