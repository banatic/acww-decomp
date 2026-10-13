/* func_020b3754 @ 0x020b3754, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Cell {
    char data[0x28];
} Cell;
typedef struct Work {
    Cell *base;
    unsigned int width;
    unsigned int height;
} Work;
extern void func_020b38dc(void *);
extern void *func_020b3880(void *);
extern Work *func_0204e414(void *);
extern unsigned short *func_02037e0c(Cell *, int, int, int);
extern void func_0204f800(int *, int *, unsigned int, unsigned int, int, int);
extern void func_0204e404(Work *, unsigned short *, int, int);
inline unsigned short inline_fn(unsigned short *arg0)
{
    return *arg0;
}

void func_020b3754(void *arg)
{
    unsigned int y;
    unsigned int x;
    int k;
    int j;
    Work *work;
    int flag = 1;
    int a;
    int b;
    Cell *ptr;
    unsigned short *res;
    int ok;
    func_020b38dc(arg);
    work = func_0204e414(func_020b3880(((char *) arg) + 4));
    for (y = 1; y <= 4; y++) {
        for (x = 1; x <= 4; x++) {
            if (((x < work->width) && (y < work->height)) && work->base) {
                ptr = work->base + (x + (y * work->width));
            } else {
                ptr = 0;
            }
            if (ptr) {
                for (k = 0; k < 16; k++) {
                    for (j = 0; j < 16; j++) {
                        res = func_02037e0c(ptr, j, k, 0);
                        if (res) {
                            ok = 0;
                            if ((inline_fn(res) >= 0x5000) && (inline_fn(res) <= 0x5021)) {
                                ok = flag;
                            }
                            if (ok) {
                                func_0204f800(&a, &b, x, y, j, k);
                                func_0204e404(work, res, a, b);
                            }
                        }
                    }
                }
            }
        }
    }
}
