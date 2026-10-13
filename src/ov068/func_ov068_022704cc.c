/* func_ov068_022704cc @ 0x022704cc, 0x1b4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d088(void *p);
extern int NNS_G3dMdlGetMdlAlpha(void *m, int i);
extern void func_ov003_022353a4(void *self, int a, int b);
extern int func_0200322c(void *a, void *b);
extern int func_020ea990(void *a, void *b);
extern void func_020e8870(short *v, int ang, int k);
extern void func_02056fcc(void *p, int a, int b, int c, int d);

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
