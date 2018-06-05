# IPC: inter-process communication

## signal

### Examples of signals

- User types control-C

- Process makes illegal memory reference

eg. SIGSEGV-- segmentation violation(segmentation fault)
 在Unix/Linux中，有时程序并未经过彻底的调试，使得它们有可能在执行的时候出现一些比如段错误之类的情况，此时可能会导致核心转储(core dumps)。
 
套用《Classis Shell Scripting》一书的解释：
“在Unix系统中，常将‘主内存’（main memory）称为核心（core），因为在使用半导体作为内存材料之前 ，便是使用核心（core）。而核心映像（core image）就是‘进程’（process）执行当时的内存内容。当进程发生错误或收到‘信号’(signal)而终止执行时，系统会将核心映像写入一个文件，以作为调试之用，这就是所谓的核心转储（core dumps）。”

在Unix/Linux中，有时程序并未经过彻底的调试，使得它们有可能在执行的时候出现一些比如段错误之类的情况，此时可能会导致核心转储(core dumps)。
 
The function to send signal:
- kill()
- raise()
- sigqueue()
- alarm()
- setitimer()
- abort()

### 利用信号灯实现PV操作（用于同步互斥）

Semaphores:
- Create semaphores: semget()
- Change semaphores: semop()


### sleep
sleep(3) - Linux man page
Name
sleep - sleep for the specified number of seconds
Synopsis

```
#include <unistd.h>
```

unsigned int sleep(unsigned int seconds);

Description
sleep() makes the calling thread sleep until seconds seconds have elapsed or a signal arrives which is not ignored.
Return Value
Zero if the requested time has elapsed, or the number of seconds left to sleep, if the call was interrupted by a signal handler. 

### if(!fork())


From the fork(2) manpage:

    Return Value

    On success, the PID of the child process is returned in the parent, and 0 is returned in the child. On failure, -1 is returned in the parent, no child process is created, and errno is set appropriately.

Since fork() returns 0 to the child, the if clause tests if it's a child:
```
if (!fork()) // same as: if (fork() == 0)
{
  // child
}else{
  // parent
}
```

## part1

## part2

## part3 


reference:
- https://blog.csdn.net/onlyonename/article/details/8120050
- https://stackoverflow.com/questions/13495783/if-fork-what-does-it-mean/13495848
- https://blog.csdn.net/u011068702/article/details/55505977
