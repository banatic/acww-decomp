/* insect_paths_3: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022704cc @ 0x022704cc, 0x1b4 bytes, Thumb
 * func_ov068_02270328 @ 0x02270328, 0x1a4 bytes, Thumb
 */

extern int func_0209d088(void *p);
extern int NNS_G3dMdlGetMdlAlpha(void *m, int i);
extern void func_ov003_022353a4(void *self, int a, int b);
extern int func_0200322c(void *a, void *b);
extern int func_020ea990(void *a, void *b);
extern int func_020e8870(short *v, int ang, int k);
extern void func_02056fcc(void *p, int a, int b, int c, int d);
extern int func_ov003_0221996c(int k);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_ov003_02232598(void *self, int k);
extern void func_ov003_02230f60(void *self);

int func_ov068_022704cc(char *self, int mode, void *arg)
{
    char *p204;
    int t232;
    short tmp;
    short *q;
    char *p50;
    int t1, t2;

    p204 = self + 0x204;
    t232 = *(short *) (self + 0x232);
    tmp = *(short *) (self + 0x23a);
    q = (short *) (self + 0x23e);
    p50 = self + 0x50;
    if (*q != 0 && *(signed char *) (self + 0x24d) != 0x37) {
        goto tail;
    }
    if (NNS_G3dMdlGetMdlAlpha((void *) func_0209d088(self + 0x130), 0) != 0x1f) {
        goto tail;
    }
    if (mode == 1) {
        if (*q == 0) {
            func_ov003_022353a4(self, 1, 0);
            tmp = func_0200322c(p204, arg);
        }
        *q = *q + 1;
    }
    if (t232 > 0) {
        *(short *) (self + 0x232) = t232 - 1;
    } else if (mode == 0) {
        *(short *) (self + 0x232) = 0x3c;
        if (*(signed char *) (self + 0x24d) == 0x37 && (unsigned short) (*(int *) (p50 + 0xa4) >> 12) < 4 &&
            (unsigned short) (*(int *) (p50 + 0xa0) >> 12) < 0xb) {
            func_ov003_022353a4(self, 1, 0);
        }
    }
    if (*(unsigned char *) (self + 0x24b) == 0) {
        goto tail;
    }
    if (func_020ea990(p204, arg) < 0x2000) {
        func_020e8870(&tmp, func_0200322c(p204, arg), 0xe38);
    } else {
        func_020e8870(&tmp, func_0200322c(p204, arg), 0x71c);
    }
    *(short *) (self + 0x23a) = tmp;
tail:
    if (*(signed char *) (self + 0x24d) != 0x37) {
        goto done;
    }
    t1 = *(int *) (p50 + 0xa0) >> 12;
    if ((unsigned short) t1 == 0xe) {
        if ((unsigned short) (*(int *) (p50 + 0xa4) >> 12) == 0xd) {
            *(int *) (p50 + 0xa4) = 0xa000;
            goto done;
        }
    }
    t2 = *(int *) (p50 + 0xa4) >> 12;
    if ((unsigned short) t2 < 4) {
        if ((unsigned short) t1 < 0xb) {
            func_02056fcc(p50 + 0x9c, 0xb, 1, 0x1000, 4);
            goto done;
        }
    }
    if ((unsigned short) t1 == 0xb) {
        if ((unsigned short) t2 == 0xa) {
            func_02056fcc(p50 + 0x9c, 0xe, 0, 0x1000, 0xa);
        }
    }
done:
    return 1;
}

int func_ov068_02270328(char *self, int mode, void *arg, short *p)
{
    int *p204;
    short *q;
    short tmp;
    int v;
    int t;

    p204 = (int *) (self + 0x204);
    if (*(unsigned char *) (self + 0x247) == 0) {
        goto other;
    }
    v = *p;
    if (v != 0 && v <= 0x1f) {
        goto other;
    }
    if (NNS_G3dMdlGetMdlAlpha((void *) func_0209d088(self + 0x130), 0) != 0x1f) {
        goto other;
    }
    if (mode == 3 || mode == 1) {
        if (func_020ea990(arg, p204) < 0x1000) {
            q = (short *) (self + 0x23e);
            if (func_ov003_0221996c(*(signed char *) (self + 0x24d) == 0x37 ? 1 : 0) != 0) {
                *(unsigned char *) (self + 0x251) = 0x13;
                *(unsigned char *) (self + 0x24c) = 1;
                func_02056fcc(self + 0xec, 0, 2, 0x1000, (int) ((unsigned int) (*(int *) (self + 0xf4) << 4) >> 16));
            } else {
                v = *q;
                if (v > 0 && *(signed char *) (self + 0x24d) == 0x36) {
                    t = FX_MulFunc(FX_Div(0x1000, 0x12000), v << 12);
                    p204[1] = p204[1] + (t + -10 * (v * v));
                    *q = *q + 3;
                    if (p204[1] <= 0) {
                        *q = 0;
                    }
                }
            }
            return 1;
        }
        *(unsigned char *) (self + 0x251) = 5;
        return 2;
    }
    if (*(unsigned char *) (self + 0x251) == 7) {
        *(unsigned char *) (self + 0x251) = 4;
        *p = 0;
    }
    goto ret0;
other:
    if (mode == 1 || mode == 3) {
        if (*p == 0) {
            *p = 0x12c;
            goto dec;
        }
    }
    if (*p < 0x1f) {
        if (func_ov003_02232598(self, 1) != 0) {
            func_ov003_02230f60(self);
        }
        goto dec;
    }
    if (*(unsigned char *) (self + 0x24b) == 0) {
        goto dec;
    }
    tmp = *(short *) (self + 0x23a);
    func_ov003_022353a4(self, 0, 1);
    func_020e8870(&tmp, func_0200322c(arg, p204), 0x666);
    *(short *) (self + 0x23a) = tmp;
    *(unsigned char *) (self + 0x251) = 7;
dec:
    *p = *p - 1;
ret0:
    return 0;
}
