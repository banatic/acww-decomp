/* func_02048e54 @ 0x02048e54, 0x72 bytes, Thumb, module main
 * mwccarm 1.2/base -O2,p
 */

struct Grid {
    void *data;
    unsigned int width;
    unsigned int height;
};

extern int func_0204eda8(struct Grid *a1, int a2, int a3);
extern int func_0204a034(void);
extern void *func_0204f5e0(struct Grid *grid, unsigned int x, unsigned int y, int p3, int p4, unsigned char p5);

int func_02048e54(struct Grid *self, int p1, int p2)
{
    int result = 0;
    int gate = func_0204eda8(self, p1, p2);
    if (gate == 0) {
        goto proceed;
    }
    if (gate != 1) {
        goto done;
    }
proceed: {
    int q, x, y, ymod;
    q = p2 + 1;
    x = p1 >> 4;
    y = q >> 4;
    ymod = q - (y << 4);
    if (func_0204f5e0(self, x, y, p1 - (x << 4), ymod, 0) == 0) {
        goto done;
    }
}
    if (func_0204a034() != 0) {
        goto done;
    }
    {
        int q, x, y, ymod;
        q = p2 + 2;
        x = p1 >> 4;
        y = q >> 4;
        ymod = q - (y << 4);
        if (func_0204f5e0(self, x, y, p1 - (x << 4), ymod, 0) == 0) {
            goto done;
        }
    }
    if (func_0204a034() != 0) {
        goto done;
    }
    result = 1;
done:
    return result;
}
