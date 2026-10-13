/* func_ov003_0221a608 @ 0x0221a608, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    unsigned short id;
} UnkStruct_0221a608;

extern void *data_021c80bc; // 0x021c80bc, the town/field map
extern int func_ov003_0221a68c(void *);
extern short func_0204bb14(void *);
extern void func_0204f818(int *, int *, void *);
extern UnkStruct_0221a608 *func_0204f5e0(void *, int, int, int, int, int);
extern int func_0204f538(void *, unsigned short *, int, int, int);

int func_ov003_0221a608(void *a, void *b, unsigned short *out)
{
    void *g;
    unsigned short h;
    int x, y;
    int hx, hy;
    UnkStruct_0221a608 *e;

    *out = 0xfff1;
    if (func_ov003_0221a68c(b) == 0) {
        goto fail;
    }
    g = data_021c80bc;
    if (g == 0) {
        goto fail;
    }
    h = func_0204bb14(a);
    func_0204f818(&x, &y, b);
    {
        int xx = x, yy = y;
        hx = xx >> 4;
        hy = yy >> 4;
        e = func_0204f5e0(g, hx, hy, xx - (hx << 4), yy - (hy << 4), 0);
    }
    if (e != 0) {
        *out = e->id;
    }
    if (func_0204f538(g, &h, x, y, 0) != 0) {
        return 1;
    }
fail:
    return 0;
}
