# Socket Programming


## TCP

### Server

Server                          Client
- socket()                      socket()
- bind()
- listen()
- accept()                      connect()
- recv()                        send()
- send()                        recv()
- close()                       close()


## 一些辅助函数

### gets

```
#include <stdio.h>

char *gets(char *s);
```

gets()  reads  a  line  from  stdin  into the buffer pointed to by s until either a terminating newline or EOF, which it
replaces with a null byte ('\0').  No check for buffer overrun is performed (see BUGS below).

Never  use gets().  Because it is impossible to tell without knowing the data in advance how many characters gets() will
read, and because gets() will continue to store characters past the end of the buffer, it is extremely dangerous to use.
It has been used to break computer security.  Use fgets() instead

### fgets






### gotoxy
To begin with, the correct code should have no spaces after the character format specifier (%c) and the opening second bracket, so that the modified line of code becomes -

    printf("%c[%d;%df", 0x1B, y, x);

Now, what this line of code does is place the cursor at row y and column x of the terminal. It is equivalent to and simulates the gotoxy() function provided by the ncurses library.

Coming to how it works,

The first character interpreted is 0x1B, which is equivalent to 27 in decimals, and is translated as the escape character (ESC) in the ASCII coding system. The rest now becomes an ANSI escape sequence and thus, is used for cursor positioning.

The actual ANSI escape sequence for cursor positioning is given as -

    \033[<L>;<C>f
         Or,
    \033[<L>;<C>H

So, yes, you may also replace the ‘f’ with ‘H’ and confirm that it also works perfectly fine. Also, to ensure further portability and consistency across systems using different encoding systems and not just ASCII, I would suggest the use of the following line of code -

    printf("\e[%d;%df", y, x);	// \e is the escape character (ESC)

Happy coding!

