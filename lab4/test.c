#include "stdio.h"

void gotoxy(int x,int y)
 {
 printf("%c[%d;%df",0x1B,y,x);
 }

int main() {
    int count = 4;
    int i = 0;
    for (i = 0; i < 4; i++){
        gotoxy(0, 4);
    }
    return 0;
}