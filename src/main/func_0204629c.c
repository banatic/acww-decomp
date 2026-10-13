/* func_0204629c @ 0x0204629c, 0x1f4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} Pt2;

typedef struct {
    unsigned char k0 : 3;
    unsigned char kind : 5;
    unsigned char m0 : 2;
    unsigned char m2 : 3;
    unsigned char m5 : 2;
    unsigned char m7 : 1;
    signed char n0 : 2;
    signed char n2 : 4;
    signed char n6 : 2;
    unsigned char pad_03[5];
    unsigned short unk_08;
    unsigned short unk_0A;
} UnkStruct_0204629c;

extern int func_020b6660(void);
extern void *func_0204e414(void);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_02045d98(int a);
extern void func_02042c58(void *a, Pt2 *p, int d, int k);
extern void func_020464d4(UnkStruct_0204629c *p);
extern void func_020465b0(UnkStruct_0204629c *p);
extern unsigned char data_021c7c48;

void func_0204629c(UnkStruct_0204629c *p)
{
    void *ctx;
    int x, y;
    int cx, cz;
    int result;
    unsigned short *o;
    int h, g, f, e, d, c, b, a;
    unsigned int v;
    int dir;
    Pt2 pt;

    result = 0;
    if (func_020b6660() == 0) {
        goto end;
    }
    ctx = func_0204e414();
    if (ctx == 0) {
        goto end;
    }
    y = p->unk_08 & 0xff;
    x = p->unk_08 >> 8;
    cx = x >> 4;
    cz = y >> 4;
    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), y - (cz << 4), 0);
    if (o == 0) {
        goto end;
    }
    switch (p->kind) {
        case 18:
            func_02045d98(p->k0);
        case 17:
        case 19:
        case 24:
        case 26:
            h = 1;
            g = 1;
            f = 1;
            e = 1;
            d = 1;
            c = 1;
            b = 1;
            a = 0;
            v = *o;
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
            if (d == 0) {
                if (!((v >= 0x8a && v <= 0x8f) || (v >= 0x90 && v <= 0x95) || (v >= 0x96 && v <= 0x9b) ||
                      (v >= 0x9c && v <= 0xa3) || v == 0xa5)) {
                    e = 0;
                }
            }
            if (e == 0) {
                if (v != 0x1a) {
                    f = 0;
                }
            }
            if (f == 0) {
                if (v != 0xa4) {
                    g = 0;
                }
            }
            if (g == 0) {
                if (v != 0x1d) {
                    h = 0;
                }
            }
            if (h == 0) {
                if (!((v >= 0x26 && v <= 0x2a) || (v >= 0x5d && v <= 0x61) || (v >= 0x2f && v <= 0x56) ||
                      (v >= 0x57 && v <= 0x5b) || (v >= 0x66 && v <= 0x68) || v == 0x69 || (v >= 0x6a && v <= 0x6c) ||
                      v == 0x6d || (v >= 0xc8 && v <= 0xcf))) {
                    if (p->m0 != 0) {
                        result = 1;
                    }
                }
            }
            break;
        case 6:
        case 7:
            if (p->m5 == 2) {
                break;
            }
            dir = p->m0;
            pt.x = x;
            pt.y = y;
            func_02042c58(&data_021c7c48, &pt, (dir + 1) & 3, 3);
            break;
        case 10:
            result = p->m0;
            break;
        case 25:
            if (p->n2 >= 0) {
                p->unk_0A = 0xfff1;
            }
            break;
    }
end:
    p->m0 = (unsigned char) result;
    func_020464d4(p);
    func_020465b0(p);
}
