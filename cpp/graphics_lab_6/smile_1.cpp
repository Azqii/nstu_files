#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>

int main() {
    /* request auto detection */
    int gdriver = DETECT, gmode, errorcode;
    clrscr();
    /* initialize graphics and local variables */
    initgraph(&gdriver, &gmode, "c: \\bgi\\");
    /* read result of initialization */
    errorcode = graphresult();
    if (errorcode != grOk) /* an error occurred */
    {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        exit(1); /* terminate with an error code */
    }
    setfillstyle(SOLID_FILL, YELLOW);
    setcolor(YELLOW);
    pieslice(100, 100, 0, 360, 20);
    setcolor(BLUE);
    circle(100 - 7, 100 - 7, 2);
    circle(100 + 7, 100 - 7, 2);
    for (int i = 0; i < 10; i++) {
        setcolor(RED);
        arc(100, 102, 180, 360, 10);
        delay(1000);
        setcolor(YELLOW);
        arc(100, 102, 180, 360, 10);
        setcolor(RED);
        arc(100, 108, 0, 180, 10);
        delay(1000);
        setcolor(YELLOW);
        arc(100, 108, 0, 180, 10);
    }
    setcolor(RED);
    arc(100, 102, 180, 360, 10);
    getch();
    closegraph();
    return 0;
}
