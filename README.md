# An xv6 Lottery Scheduler

In this project, a new **scheduler** was put into **xv6**. It is called a
**lottery scheduler**, and the full version is described in [this chapter](http://www.cs.wisc.edu/~remzi/OSFEP/cpu-sched-lottery.pdf).  The basic idea is simple:
- assign each running process a **slice** of the processor based in proportion to the **number of tickets** it has; the more tickets a process has, the more it runs. 
- Each time slice, a randomized lottery determines the winner of the lottery; that winning process is the one that runs for that time slice.
## Details

Two new system calls are needed to implement this scheduler. The first is
`int settickets(int number)`, which sets the number of tickets of the calling
process. By default, each process should get one ticket; calling this routine
makes it such that a process can raise the number of tickets it receives, and
thus receive a higher proportion of CPU cycles. This routine returns 0
if successful, and -1 otherwise (if, for example, the caller passes in a
number less than one).

The second is `int getpinfo(struct pstat *)`. This routine returns some
information about all running processes, including how many times each has
been chosen to run and the process ID of each. This system call is used to
build a variant of the command line program `ps`, which can then be called to
see what is going on. The structure `pstat` is defined below. This routine
returns 0 if successful, and -1 otherwise (if, for example, a bad or NULL
pointer is passed into the kernel).

```
#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
  int inuse[NPROC];   // whether this slot of the process table is in use (1 or 0)
  int tickets[NPROC]; // the number of tickets this process has
  int pid[NPROC];     // the PID of each process 
  int ticks[NPROC];   // the number of ticks each process has accumulated 
};

#endif // _PSTAT_H_
```

Most of the code for the scheduler is quite localized and can be found in
`proc.c`.

Tickets are assigned to a process when it is created. Specifically, a child process *inherits* the same number of tickets as its parents. Thus, if the parent has 10 tickets, and calls **fork()** to create a child process, the child gets 10 tickets.

Random numbers in the kernel are generated using simple pseudo-random number generator.

## Procedures to run xv6
Inside Ticket_To_XV6, Run qemu emulator in command prompt:
```
make
make qemu-nox
```
Now, You can check if system `ticket` system call exist or not by using `ls`. Your output should be like this:
```
$ ls
.              1 1 512
..             1 1 512
README         2 2 4166
cat            2 3 17124
echo           2 4 15916
forktest       2 5 9608
grep           2 6 20428
init           2 7 16556
kill           2 8 16008
ln             2 9 15880
ls             2 10 18592
mkdir          2 11 16020
rm             2 12 15996
sh             2 13 31612
stressfs       2 14 17020
ticket         2 15 16212
procInfo       2 16 16592
null           2 17 16208
usertests      2 17 67560
wc             2 18 17660
zombie         2 19 15548
console        3 20 0
$
```
You can call `ticket` to create a process. Also to see how the lottery scheduling is done to assigned processes use :
```
ticket [Number of tickets for the process]&; procInfo
```
or you can assign tickets to multiple processes at one command like this one:
```
ticket 10&; ticket 15&; ticket 20&; ticket 25&; ticket 30&; procInfo
```

## Read-only Code

In xv6, the VM system uses a simple two-level page table and as it currently is structured, user code is loaded into the very first part of the address space. In most operating systems, code is marked read-only instead of read-write. However, in xv6 this is not the case, so a buggy program could accidentally overwrite its own text.


The protection bits of parts of the page table is changed to be read-only, thus preventing such over-writes, and also be able to change them back. To do this, two system calls is added: `int mprotect(void *addr, int len)` and `int munprotect(void *addr, int len)`.

Calling `mprotect()` should change the protection bits of the page range starting at `addr` and of `len` pages to be read only. Thus, the program could still read the pages in this range after `mprotect()` finishes, but a write to this region should cause a trap (and thus kill the process). The `munprotect()` call does the opposite: sets the region back to both readable and writable.

The page protections should be inherited on `fork()`. Thus, if a process has protected some of its pages, when the process calls fork, the OS should copy those protections to the child process.

Failure cases are considered: if `addr` is not page aligned, or `addr` points to a region that is not currently a part of the address space, or `len` is less than or equal to zero, return -1 and do not change anything. Otherwise, return 0 upon success.

After changing a page-table entry, the hardware need to know of the change. On 32-bit x86, this is readily accomplished by updating the `CR3` register. When the hardware sees that `CR3` was overwritten (even with the same value), it guarantees that PTE updates will be used upon subsequent accesses.
