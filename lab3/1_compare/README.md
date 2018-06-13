# 文件读写相关函数

##　open、read、write

##　fopen、fread、fwrite

### fopen

通过man fopen 可以看到fopen的定义

```
#include <stdio.h>

FILE *fopen(const char *pathname, const char *mode);
```


       r      Open text file for reading.  The stream is  posi‐
              tioned at the beginning of the file.

       r+     Open  for  reading  and  writing.   The stream is
              positioned at the beginning of the file.

       w      Truncate file to zero length or create text  file
              for  writing.   The  stream  is positioned at the
              beginning of the file.

       w+     Open for reading and writing.  The file  is  cre‐
              ated  if it does not exist, otherwise it is trun‐
              cated.  The stream is positioned at the beginning
              of the file.

       a      Open for appending (writing at end of file).  The
              file is created if it does not exist.  The stream
              is positioned at the end of the file.

       a+     Open for reading and appending (writing at end of
              file).  The file is created if it does not exist.
              The  initial  file position for reading is at the
              beginning of  the  file,  but  output  is  always
              appended to the end of the file.


The file descriptor associated with the stream is opened as if by a call to open(2) with the following flags:

              ┌─────────────┬───────────────────────────────┐
              │fopen() mode │ open() flags                  │
              ├─────────────┼───────────────────────────────┤
              │     r       │ O_RDONLY                      │
              ├─────────────┼───────────────────────────────┤
              │     w       │ O_WRONLY | O_CREAT | O_TRUNC  │
              ├─────────────┼───────────────────────────────┤
              │     a       │ O_WRONLY | O_CREAT | O_APPEND │
              ├─────────────┼───────────────────────────────┤
              │     r+      │ O_RDWR                        │
              ├─────────────┼───────────────────────────────┤
              │     w+      │ O_RDWR | O_CREAT | O_TRUNC    │
              ├─────────────┼───────────────────────────────┤
              │     a+      │ O_RDWR | O_CREAT | O_APPEND


### fread


### fwrite
