/* func_ov003_0221a68c @ 0x0221a68c, 0x114 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off

extern int data_021c80bc;

extern void *func_020961a8(int a);
extern void func_0204f818(int *x, int *y, void *pos);
extern void *func_0204f5e0(int g, int qx, int qy, int rx, int ry, int f);
extern int func_0204c71c(unsigned short *entry);
extern int func_02031078(int x, int y, int *u, int *v, int *w);
extern int func_02031b38(int x, int y);
extern int func_02031acc(int x, int y);

int func_ov003_0221a68c(void *pos)
{
    int g;
    void *p;
    int ax, ay;
    int u, v, w;
    int bx, by;
    int qx, qy;
    int c0;
    unsigned short *entry;
    int r;
    // DECLS
    int dy;
    int dx;
    // ENDDECLS
    int lx, ly;
    int t, n;
    int c;

    g = data_021c80bc;
    if (g != 0) {
        ax = -1;
        ay = -1;
        p = func_020961a8(4);
        if (p != 0) {
            func_0204f818(&ax, &ay, (char *) p + 0x5c);
        }
        func_0204f818(&bx, &by, pos);
        lx = bx;
        ly = by;
        qx = lx >> 4;
        qy = ly >> 4;
        if ((entry = func_0204f5e0(g, qx, qy, bx - (qx << 4), by - (qy << 4), 0)) != 0) {
            if (func_0204c71c(entry) != 0) {
                return 0;
            }
        }
        c0 = func_02031078(bx, by, &u, &v, &w);
        if (bx != ax || by != ay) {
            if (func_02031b38(bx, by) != 0) {
                if (c0 == 0 || (c0 != 0 && w == 2)) {
                    r = func_02031acc(bx, by);
                    switch (r) {
                        case 0:
                        case 1: {
                            for (dy = -1; dy <= 1; dy++) {
                                for (dx = -1; dx <= 1; dx++) {
                                    if (dy != 0 || dx != 0) {
                                        n = by + dx;
                                        t = bx + dy;
                                        c = func_02031078(t, n, &u, &v, &w);
                                        if (func_02031b38(t, n) == 0 || (c != 0 && w != 2)) {
                                            return 0;
                                        }
                                    }
                                }
                            }
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
