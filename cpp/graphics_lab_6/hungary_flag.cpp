#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#define PATHTODRIVER "c: \\bgi\\"

void hungaryflag(int x, int y, int l, int h) {
    int w = h / 3;

    setfillstyle(SOLID_FILL, RED);
    bar(x, y, x + l, y + w);
    setfillstyle(SOLID_FILL, WHITE);
    bar(x, y + w, x + l, y + 2 * w);
    setfillstyle(SOLID_FILL, GREEN);
    bar(x, y + 2 * w, x + l, y + 3 * w);
    outtextxy(x, y + h + 5, "HUNGARY\0");
}

void main() {
    int gdriver = DETECT;
    int gmode;
    int errorcode;

    initgraph(&gdriver, &gmode, PATHTODRIVER);
    errorcode = graphresult();
    if (errorcode != grOk) {
        printf("Error: %d\n", errorcode);
        puts("Press <Enter> to stop");
        getch();
        return;
    }

    hungaryflag(100, 100, 50, 25);
    getch();
    closegraph();
}
