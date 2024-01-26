#include <graphics.h>
#include <stdio.h>
#include <conio.h>

#define PATHTODRIVER "c:\\bgi\\"
#define height 479
#define width 639

void square(int dx, int dy) {
    int lx = 0;
    int rx = width;

    int ty = 0;
    int by = height;
    int index = 0;

    int num_x = width / (2 * dx);
    int num_y = height / (2 * dy);

    int num = (num_x < num_y) ? num_x : num_y;

    for (int i = 0; i < num; i++) {
        index = i % 16;
        setfillstyle(SOLID_FILL, index);
        bar(lx, ty, rx, by);
        if (lx < width / 2) {
            lx += dx;
            rx -= dx;
        }
        if (ty < height / 2) {
            ty += dy;
            by -= dy;
        }
    }
}

int main() {
    int gdriver = DETECT;
    int gmode;
    int errorcode;
    int dx, dy;

    printf("Enter dx: ");
    scanf("%d", &dx);
    printf("Enter dy: ");
    scanf("%d", &dy);

    if (dx <= 0 || dy <= 0) {
        printf("Invalid input\n");
        getch();
        return -1;
    }

    initgraph(&gdriver, &gmode, PATHTODRIVER);
    errorcode = graphresult();

    if (errorcode != grOk) {
        printf("Error: %d\n", errorcode);
        getch();
        return -1;
    }

    square(dx, dy);

    getch();
    closegraph();
    return 0;
}
