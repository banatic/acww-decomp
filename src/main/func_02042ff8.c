/* func_02042ff8 @ 0x02042ff8, 0x1c0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

typedef struct {
    int x;
    int y;
} Pt;

extern void *func_0204e414(void);
extern void *func_020961a8(int);
extern int func_02044808(void *);
extern int func_02045cec(Pt *, int);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern unsigned short func_020475b0(void *tbl, unsigned short *o, int flag);
extern int func_020b65c4(void);
extern void func_0205f9d4(int x, int z, int t, int r, int zero);
extern int func_02073d90(void *);
extern void func_0204f794(void *w, int x, int y);
extern void func_020796e4(void *w);

extern signed char data_020ca584[];
extern signed char data_020ca58c[];
extern unsigned char data_021c779c;
extern void *data_020ccf94;

void func_02042ff8(void *self, Pt *p)
{
    int flagA;
    int found;
    int i;
    void *ctx;
    void *q;
    unsigned short *o;
    int z;
    unsigned short r;
    int x;
    int cx, cz;
    unsigned int v;
    int d, c, b, a;
    int t;
    signed char *dx;
    signed char *dz;
    Pt pt;
    char w[12];

    ctx = func_0204e414();
    q = func_020961a8(4);
    if (ctx == 0) {
        return;
    }
    if (q == 0) {
        return;
    }

    flagA = 0;
    found = 0;
    if (func_02044808(self) == 0x1379) {
        flagA = 1;
    }

    dx = data_020ca584;
    dz = data_020ca58c;
    for (i = 0; i < 5; i++) {
        x = p->x + *dx;
        z = p->y + *dz;
        pt.x = x;
        pt.y = z;
        if (func_02045cec(&pt, 0) < 0) {
            cx = x >> 4;
            cz = z >> 4;
            o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
            if (o != 0) {
                r = func_020475b0(&data_021c779c, o, flagA);
                if (r != 0xfff1) {
                    found = 1;
                    t = func_020b65c4();
                    func_0205f9d4((signed char) x, (signed char) z, t, r, 0);
                }
                v = *o;
                d = 1;
                c = 1;
                b = 1;
                a = 0;
                if (v <= 5) {
                    a = 1;
                }
                if (a == 0) {
                    if (!(v >= 6 && v <= 0xb)) {
                        b = 0;
                    }
                }
                if (b == 0) {
                    if (!(v >= 0xc && v <= 0x11)) {
                        c = 0;
                    }
                }
                if (c == 0) {
                    if (!((v >= 0x12 && v <= 0x19) || v == 0x1c)) {
                        d = 0;
                    }
                }
                if (d != 0 || (v >= 0x8a && v <= 0x8f) || (v >= 0x90 && v <= 0x95) || (v >= 0x96 && v <= 0x9b) ||
                    (v >= 0x9c && v <= 0xa3) || v == 0xa5 || (v >= 0x6e && v <= 0x73) || (v >= 0x74 && v <= 0x79) ||
                    (v >= 0x7a && v <= 0x7f) || (v >= 0x80 && v <= 0x87) || v == 0x1a || v == 0x88 || v == 0xa4 ||
                    (unsigned short) (v + 0xffe3) <= 1) {
                    found = 1;
                }
            }
        }
        dx++;
        dz++;
    }
    if (found != 0) {
        if (func_02073d90(data_020ccf94) == 0) {
            func_0204f794(w, p->x, p->y);
            func_020796e4(w);
        }
    }
}
