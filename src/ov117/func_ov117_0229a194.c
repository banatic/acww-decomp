/* func_ov117_0229a194 @ 0x0229a194, 0xd8 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

typedef struct Map {
    void *tiles;
    unsigned int width;
    unsigned int height;
} Map;

extern void func_02030e4c(int);
extern Map *func_0204e414(void);
extern int func_02037d9c(void *);
extern int func_02031498(int *, int *, int, int);
extern void func_ov117_0229a2a4(void *, int, int, int, int);

void func_ov117_0229a194(void *arg)
{
    Map *map;
    int row, col;
    int bx, by;
    int mode, count;
    void *tile;

    func_02030e4c(1);
    count = 0;
    map = func_0204e414();

    for (row = 1; row < 5; row++) {
        for (col = 1; col < 5; col++) {
            if (col < map->width && row < map->height && map->tiles != 0) {
                tile = (char *) map->tiles + 0x28 * (col + row * map->width);
            } else {
                tile = 0;
            }

            if ((func_02037d9c(tile) & 4) != 0) {
                mode = func_02031498(&bx, &by, col, row);

                if (mode != 4) {
                    bx *= 2;
                    by *= 2;
                    bx += 1;
                    by += 1;

                    switch (mode) {
                        case 0:
                            bx += 1;
                            by += 3;
                            break;
                        case 1:
                            bx += 3;
                            by += 1;
                            break;
                        case 2:
                            by += 4;
                            break;
                        case 3:
                            bx += 2;
                            by += 4;
                            break;
                    }

                    func_ov117_0229a2a4(arg, count, bx, by, (unsigned char) mode);
                    count++;
                }
            }
        }
    }

    func_02030e4c(0);
}
