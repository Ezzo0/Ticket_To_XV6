#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "param.h"

#define PGSIZE 4096

// void test_1(void)
// {
//     const uint PAGES_NUM = 1;
    
//     char *ptr = sbrk(PAGES_NUM * PGSIZE);
//     printf(1, "XV6_TEST_OUTPUT %d\n", mprotect(ptr, -10));
//     printf(1, "XV6_TEST_OUTPUT %d\n", mprotect(ptr, PAGES_NUM + 10));
// }

// void test_2(void)
// {
//     const uint PAGES_NUM = 5;
    
//     // Allocate 5 pages
//     char *ptr = sbrk(PGSIZE * PAGES_NUM * sizeof(char));
//     mprotect(ptr, PAGES_NUM);
//     int ppid = getpid();

//     if (fork() == 0) {
//         // Should page fault as normally here
//         ptr[2 * PGSIZE] = 0xAA;
//         printf(1, "XV6_TEST_OUTPUT Seg fault failed to trigger\n");
//         // Shouldn't reach here
//         kill(ppid);
//         exit();
//     } else {
//         wait();
//     }

//     printf(1, "XV6_TEST_OUTPUT TEST PASS\n");
// }

// void test_3(void)
// {
//     const uint PAGES_NUM = 5;
    
//     // Allocate 5 pages
//     char *ptr = sbrk(PGSIZE * PAGES_NUM * sizeof(char));
//     mprotect(ptr, PAGES_NUM);
//     ptr[PGSIZE * 3] = 0xAA;
//     printf(1, "XV6_TEST_OUTPUT TEST PASS\n");
// }

// void test_4(void)
// {
//     const uint PAGES_NUM = 5;
    
//     // Allocate 5 pages
//     char *ptr = sbrk(PGSIZE * PAGES_NUM * sizeof(char));
//     mprotect(ptr, PAGES_NUM);
//     munprotect(ptr, PAGES_NUM);
    
//     ptr[PGSIZE * 1] = 0xAA;
//     printf(1, "XV6_TEST_OUTPUT TEST PASS\n");
// }

// void test_5(void)
// {
//     const uint PAGES_NUM = 5;
    
//     // Allocate 5 pages
//     char *ptr = sbrk(PGSIZE * PAGES_NUM * sizeof(char));
//     mprotect(ptr, PAGES_NUM);

//     if (fork() == 0) {
//         // Should NOT page fault 
//         munprotect(ptr, PAGES_NUM);
//         ptr[4 * PGSIZE] = 0xAA;
//         printf(1, "XV6_TEST_OUTPUT TEST PASS\n");
//         exit();
//     } else {
//         wait();
//     }
// }



int main(int argc, char *argv[])
{
    // unsigned char *ptr = 0x00;

    // printf(1, "ptr = %x\n", *ptr);
    
    // Allocate 5 pages
    const uint PAGES_NUM = 5;
    char *ptr = sbrk(PGSIZE * PAGES_NUM * sizeof(char));
    mprotect(ptr, PAGES_NUM);
    int x = ptr[PGSIZE * 3];
    munprotect(ptr, PAGES_NUM);
    ptr[PGSIZE * 3] = 22;
    x = ptr[PGSIZE * 3];
    printf(1, "XV6_TEST_PASS with x = %d\n", x);

    exit();
}