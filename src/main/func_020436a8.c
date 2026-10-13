/* func_020436a8 @ 0x020436a8, 0x188 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} UnkStruct_020436a8;
typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020436a8_2;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned short unk_10;
    unsigned short unk_12;
    int unk_14;
    int unk_18;
    unsigned char unk_1C;
    unsigned char pad[7];
} UnkStruct_020436a8_3;

typedef struct {
    unsigned char pad[0x64];
    int unk_64;
} UnkStruct_020436a8_4;

typedef struct {
    unsigned char pad[0x5c];
    UnkStruct_020436a8_2 v;
} UnkStruct_020436a8_5;

extern UnkStruct_020436a8_3 data_021c7c48[];
extern void *data_021c80bc;
extern UnkStruct_020436a8_4 *data_020ccf94;
extern unsigned short data_020ca664[];

extern int func_02073d90(UnkStruct_020436a8_4 *g);
extern void *func_0204f5e0(void *h, int hx, int hy, int lx, int ly, int z);
extern UnkStruct_020436a8_5 *func_020961a8(int n);
extern int func_0204ba94(volatile unsigned short *p);
extern int func_0204b710(volatile unsigned short *p);
extern void func_02045f08(UnkStruct_020436a8 *p, int a);
extern void func_ov003_02220e20(int a, int b, UnkStruct_020436a8 *p, UnkStruct_020436a8_2 *v);
extern void func_ov003_02221118(int a, int b, UnkStruct_020436a8 *p);

int func_020436a8(unsigned int idx)
{
    UnkStruct_020436a8_3 *e;
    void *h;
    int res;
    UnkStruct_020436a8_4 *g;
    unsigned short *pp;
    int m;
    int n;
    UnkStruct_020436a8_5 *q;
    UnkStruct_020436a8_2 *vp;
    int ok;
    unsigned short lo;
    unsigned short hi;
    volatile unsigned short t;
    UnkStruct_020436a8 pt;
    UnkStruct_020436a8 pt2;
    UnkStruct_020436a8 pt3;
    UnkStruct_020436a8_2 vec;
    int x, y, hx, hy;

    h = data_021c80bc;
    res = 0;
    e = &data_021c7c48[idx];
    if (e->unk_08 == 0 || e->unk_0C == 0 || (g = data_020ccf94, func_02073d90(g) != 0 && e->unk_00 != g->unk_64)) {
        return 2;
    }
    if (h == 0) {
        return 0;
    }
    x = e->unk_14;
    y = e->unk_18;
    hx = x >> 4;
    hy = y >> 4;
    pp = (unsigned short *) func_0204f5e0(h, hx, hy, x - (hx << 4), y - (hy << 4), 0);
    if (pp == 0) {
        return 0;
    }
    switch (e->unk_08) {
        case 2:
            switch (e->unk_0C) {
                case 0x13:
                    if (e->unk_10 != 0xfff1) {
                        q = func_020961a8(4);
                        if (q != 0) {
                            m = e->unk_12;
                            vp = &q->v;
                            t = 0xfff1;
                            t = e->unk_10;
                            if (func_0204ba94(&t) != 0) {
                                ok = 0;
                                lo = t;
                                hi = t;
                                if (hi >= 0x2f && lo <= 0x56) {
                                    ok = 1;
                                }
                                if (ok != 0) {
                                    m = data_020ca664[func_0204b710(&t)];
                                } else if (e->unk_10 == 0xc8) {
                                    m = 0x1548;
                                }
                            }
                            vec.a = vp->a;
                            vec.b = vp->b;
                            vec.c = vp->c;
                            pt.x = e->unk_14;
                            pt.y = e->unk_18;
                            func_ov003_02220e20(e->unk_00, m, &pt, &vec);
                        }
                    }
                    res = 1;
                    break;
                case 3:
                case 0x15:
                    if (pp[0] == 0xfff1) {
                        n = e->unk_1C;
                        pt2.x = e->unk_14;
                        pt2.y = e->unk_18;
                        func_02045f08(&pt2, n);
                        res = 2;
                    } else {
                        res = 1;
                    }
                    break;
                case 0x18:
                case 0x1a:
                    if (func_02073d90(g) == 0) {
                        pt3.x = e->unk_14;
                        pt3.y = e->unk_18;
                        func_ov003_02221118(e->unk_00, e->unk_10, &pt3);
                    }
                    res = 1;
                    break;
                default:
                    res = 1;
                    break;
            }
            break;
        case 3:
            res = 2;
            break;
    }
    return res;
}
