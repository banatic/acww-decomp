/* func_ov003_0222d83c @ 0x0222d83c, 0x23c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int m[12];
} Mtx;

extern unsigned char data_ov003_02260e4c[];
extern int FX_MulFunc(int a, int b);
extern void func_ov003_0222e358(void *p, int a);
extern int func_0203f7d0(int *dst, int *src);
extern void func_02056fcc(void *a, int b, int c, int d, int e);
extern void func_020550e4(void *a, int b);
extern void func_0209129c(int h);

int func_ov003_0222d83c(int idx, short *ptr, Mtx *src, int flag)
{
    unsigned char *p;
    int *d;
    int *mp;
    int ret;
    short ty;
    char *q;
    int v;
    int st;

    p = data_ov003_02260e4c + idx * 0x25c;
    d = (int *) (p + 0x204);
    ret = 1;
    mp = (int *) (p + 0x180);
    *(Mtx *) mp = *src;
    mp = (int *) (p + 0x180);
    func_ov003_0222e358(p, *ptr);
    d[0] = mp[9];
    d[1] = mp[10];
    d[2] = mp[11];
    func_0203f7d0(d, d);
    if (p[0x251] != 0xb) {
        ty = *(signed char *) (p + 0x24d);
        if (ty == 0x1a) {
            *(short *) (p + 0x238) = 0;
            *(short *) (p + 0x23a) = (short) FX_MulFunc(0xb6, 0xc8000);
            *(short *) (p + 0x23c) = (short) FX_MulFunc(0xb6, 0x1e000);
        } else if (ty == 0xc || ty == 0xd || ty == 0x1d) {
            *(short *) (p + 0x238) = (short) FX_MulFunc(0xb6, 0x91000);
            *(short *) (p + 0x23a) = (short) FX_MulFunc(0xb6, 0xc8000);
            *(short *) (p + 0x23c) = (short) FX_MulFunc(0xb6, 0x96000);
        } else if (ty == 0x35) {
            *(short *) (p + 0x238) = (short) FX_MulFunc(0xb6, 0x91000);
            *(short *) (p + 0x23a) = (short) FX_MulFunc(0xb6, 0x64000);
            *(short *) (p + 0x23c) = 0;
        } else {
            *(short *) (p + 0x238) = (short) FX_MulFunc(0xb6, 0x35000);
            *(short *) (p + 0x23a) = (short) FX_MulFunc(0xb6, 0xc8000);
            *(short *) (p + 0x23c) = (short) FX_MulFunc(0xb6, 0x54000);
            if (p[0x250] == 3) {
                q = (char *) (p + 0x50);
                if (ty == 0x14 && (unsigned short) (*(int *) (q + 0xa4) >> 12) == 0) {
                    func_02056fcc(q + 0x9c, 4, 1, 0x1000, 0);
                    *(int *) (q + 0xa4) = 0x4000;
                } else if (ty == 0xa || ty == 0xb) {
                    if ((unsigned short) (*(int *) (q + 0xa4) >> 12) == 0) {
                        func_020550e4(q, 1);
                    } else {
                        func_020550e4(q, 0);
                    }
                } else if (ty == 0x37) {
                    v = *(int *) (q + 0xa0) >> 12;
                    if ((unsigned short) v == 0xe && (unsigned short) (*(int *) (q + 0xa4) >> 12) == 0xd) {
                        *(int *) (q + 0xa4) = 0xa000;
                    } else if ((unsigned short) v != 0xe) {
                        func_02056fcc(q + 0x9c, 0xe, 0, 0x1000, 0xa);
                    }
                }
            }
        }
    }
    st = p[0x250];
    if (st == 2 || st == 0) {
        ret = 0;
    }
    if (flag != 0) {
        p[0x251] = 0xa;
        if (*(signed char *) (p + 0x24d) == 0x39) {
            if (*(int *) (p + 0x22c) != -1) {
                func_0209129c(*(int *) (p + 0x22c));
                *(int *) (p + 0x22c) = -1;
            }
        }
    }
    return ret;
}
