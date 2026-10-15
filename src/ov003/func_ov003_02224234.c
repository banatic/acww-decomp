/* func_ov003_02224234 @ 0x02224234, 0x150 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223cf70;
extern int func_ov003_022243d0(void *a0, int *p);
extern int func_0204e414(void);
extern int func_0204f5e0(int t, int xs, int zs, int xf, int zf, int m);
extern int func_ov003_022245a8(void *a0, int *p);
extern int func_02045c60(void *a0, int *p, int m);
extern int func_0204a034(unsigned short *tile);
extern void func_ov003_02223680(char *w, void *a0, int *p, int k, int m);

void func_ov003_02224234(void *a0, int *pos, int k)
{
    int t;
    int tile;
    int p0[2];
    int p1[2];
    int p2[2];
    int p3[2];
    int p4[2];
    int p5[2];
    p0[0] = pos[0];
    p0[1] = pos[1];
    if (func_ov003_022243d0(a0, p0) == 0) {
        return;
    }
    t = func_0204e414();
    {
        int x = pos[0];
        int z = pos[1];
        int xs = x >> 4;
        int zs = z >> 4;
        func_0204f5e0(t, xs, zs, x - (xs << 4), z - (zs << 4), 0);
    }
    switch (k) {
        case 4: {
            p1[0] = pos[0];
            p1[1] = pos[1];
            if (func_ov003_022245a8(a0, p1) == 0) {
                k = 0;
            } else {
                p2[0] = pos[0];
                p2[1] = pos[1];
                if (func_02045c60(a0, p2, 0) >= 0) {
                    int x = pos[0];
                    int xx = x - 2;
                    int z = pos[1];
                    int xs = xx >> 4;
                    int zs = z >> 4;
                    if ((tile = func_0204f5e0(t, xs, zs, xx - (xs << 4), z - (zs << 4), 0)) &&
                        func_0204a034((unsigned short *) tile)) {
                        k = 6;
                    } else if (x - 2 < 0x10) {
                        k = 6;
                    }
                } else {
                    k = 0;
                }
            }
        } break;
        case 5: {
            p3[0] = pos[0];
            p3[1] = pos[1];
            if (func_ov003_022245a8(a0, p3) == 0) {
                k = 0;
            } else {
                p4[0] = pos[0];
                p4[1] = pos[1];
                if (func_02045c60(a0, p4, 0) >= 0) {
                    int x = pos[0];
                    int xx = x + 2;
                    int z = pos[1];
                    int xs = xx >> 4;
                    int zs = z >> 4;
                    if ((tile = func_0204f5e0(t, xs, zs, xx - (xs << 4), z - (zs << 4), 0)) &&
                        func_0204a034((unsigned short *) tile)) {
                        k = 7;
                    } else if (x + 2 >= 0x50) {
                        k = 7;
                    }
                } else {
                    k = 0;
                }
            }
        } break;
    }
    p5[0] = pos[0];
    p5[1] = pos[1];
    func_ov003_02223680((char *) data_ov003_0223cf70 + 0x4b20, a0, p5, k, 1);
}
