/* func_ov003_02236274 @ 0x02236274, 0x100 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *cells;
    unsigned int w;
    unsigned int h;
} Grid;

typedef struct {
    int x, y, z;
} Vec3;

extern __arm int func_02037e0c(void *acre, int x, int z, int w);
extern int func_02037e44(void *acre, unsigned short *v, int x, int z, int w);
extern int func_0204bb54(int it);
extern int func_0204bb2c(int it);
extern int func_020b0594(char *base, unsigned int index, int *o1, int *o2, int *o3, unsigned char *o4, unsigned char *o5,
                         unsigned char *o6);
extern void func_0204f7ac(void *out, unsigned int ax, unsigned int ay, int x, int z);
extern int func_02003348(int chan, int slot, void *arg, int d, void *self);

extern unsigned char data_021c80bc[];
extern unsigned char data_021f3b56[];

void func_ov003_02236274(void *self)
{
    Grid *g;
    unsigned int ay, ax;
    int i, j;
    int n;
    void *acre;
    int it;
    int idx;
    unsigned short tmp;
    Vec3 out;

    g = *(Grid **) data_021c80bc;
    for (ay = 1; ay <= 4; ay++) {
        for (ax = 1; ax <= 4; ax++) {
            if (ax < g->w && ay < g->h && g->cells != 0) {
                acre = (char *) g->cells + (ax + ay * g->w) * 0x28;
            } else {
                acre = 0;
            }
            if (acre == 0) {
                continue;
            }
            for (i = 0; i < 0x10; i++) {
                for (j = 0; j < 0x10; j++) {
                    it = func_02037e0c(acre, j, i, 0);
                    if (it == 0) {
                        continue;
                    }
                    if (func_0204bb54(it) == 0) {
                        continue;
                    }
                    idx = func_0204bb2c(it);
                    if (func_020b0594((char *) data_021f3b56, idx, 0, 0, 0, 0, 0, 0) == 0) {
                        tmp = 0xfff1;
                        func_02037e44(acre, &tmp, j, i, 0);
                        continue;
                    }
                    n = idx * 2 + 2;
                    func_0204f7ac(&out, ax, ay, j, i);
                    func_02003348(0xbd, n, &out, 0, self);
                    func_02003348(0xbd, n + 1, &out, 0, self);
                }
            }
        }
    }
}
