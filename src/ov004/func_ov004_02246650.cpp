/* func_ov004_02246650 @ 0x02246650, 0xcc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off
extern "C" {
extern int *func_ov004_022468b0(void);
extern void *data_021c80bc;
extern unsigned short *func_0204f5e0(void *, int, int, int, int, int);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern int func_0204f538(void *, unsigned short *, int, int, int);
}
static inline bool is_empty(unsigned short *p)
{
    if (func_0204bcdc(p)) {
        unsigned short empty = 0xfff1;
        return func_0204bc64(p) == func_0204bc64(&empty);
    } else {
        return *p == 0xfff1;
    }
}

static inline unsigned short *lookup(void *g, int x, int y)
{
    int ax = x >> 4, ay = y >> 4;
    return func_0204f5e0(g, ax, ay, x - (ax << 4), y - (ay << 4), 0);
}

static inline int place(void *g, unsigned short *p, int x, int y)
{
    return func_0204f538(g, p, x, y, 0);
}

extern "C" int func_ov004_02246650(void *self, unsigned short *item, int key)
{
    int *base = func_ov004_022468b0();
    void *glob = data_021c80bc;
    if (glob) {
        for (int y = 0; y < 16; ++y) {
            int *row;
            int x;
            for (x = 0, row = base + y * 16; x < 16; ++x) {
                unsigned short *p = lookup(glob, x, y);
                if (p && is_empty(p) && key == row[x]) {
                    if (place(glob, item, x, y)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
