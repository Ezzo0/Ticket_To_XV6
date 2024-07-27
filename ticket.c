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
    

    printf(1, "----------------- Ticket Process -----------------\n");

    int number = atoi(argv[1]);
    int ret = settickets(number);

    if (ret == -1)
    {
        printf(1, "Failed to set process' tickets\n");
        exit();
    }

    

    while (1)
        ; // Infinite loop to keep the process running
    

    exit(); // eq to return zero
}
