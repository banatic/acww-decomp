/* func_0204f490 @ 0x0204f490, 0xa6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x28];
} Cell;

typedef struct {
    int w, h;
} Size;

typedef struct {
    Cell *cells;
    Size size;
} Grid;

extern int func_02037d80(Cell *c, int a);
extern int func_02037da8(Cell *c, int a, int b, int c2, int d, int e);

int func_0204f490(Grid *g, int *outX, int *outY, int p3, int p4, int p5, int p6, int p7, int p8)
{
    Size *sz = &g->size;
    int w = sz->w;
    int h = sz->h;
    int x, y;
    Cell *cell;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            if ((unsigned int) x < (unsigned int) g->size.w && (unsigned int) y < (unsigned int) g->size.h && g->cells != 0) {
                cell = &g->cells[y * g->size.w + x];
            } else {
                cell = 0;
            }
            if (cell != 0 && func_02037d80(cell, p7) != 0 && func_02037da8(cell, p3, p4, p5, p6, p8) != 0) {
                *outX = x;
                *outY = y;
                return 1;
            }
        }
    }
    return 0;
}
