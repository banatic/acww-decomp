/* func_020521d8 @ 0x020521d8, 0x20c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short x, y;
} Pt;

typedef struct {
    unsigned int b0 : 1;
    unsigned int b1 : 4;
    unsigned int b5 : 4;
    unsigned int b9 : 1;
    unsigned int b10 : 1;
    unsigned int b11 : 16;
} BF;

typedef struct {
    int unk_00, w1;
} It;

extern unsigned char data_020e54a8;
extern void *data_021c80bc;
extern void *data_020ccf94;
extern int func_020b65c4(void);
extern void *func_0204d5c8(int a);
extern void func_02052e3c(It *it, unsigned short *src);
extern Pt *func_02052dc0(It *it, unsigned int i);
extern unsigned int func_02052e20(It *it);
extern void func_02052e38(It *it);
extern int func_0204f538(void *o, unsigned short *p, int x, int y, int q);
extern void func_02052ee8(int x, int y, int a, int b, int c);
extern void func_02052e70(int x, int y, int a);
extern int func_02073d90(void *g);
extern void func_02073820(void *g);
extern void func_020737f0(void *g, void *p, int n);
extern void func_02073770(void *g, int off, int n);

void func_020521d8(int a0, int a1, int a2, int a3, int a4, unsigned short *a5, int a6, unsigned char a7)
{
    void *obj;
    unsigned int i;
    int X, Y;
    int flag;
    unsigned int ok;
    unsigned short L[4];
    It it;
    BF bf;
    void *g;
    unsigned int t;

    L[0] = *a5;
    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t > 0 && a0 == func_020b65c4()) {
        obj = data_021c80bc;
    } else {
        obj = func_0204d5c8(a0);
    }
    if (obj == 0) {
        return;
    }
    func_02052e3c(&it, a5);
    flag = 0;
    if (*a5 >= 0x45dc && *a5 <= 0x47d7) {
        flag = 1;
    }
    for (i = 0; i < func_02052e20(&it); i++) {
        X = a1 + func_02052dc0(&it, i)->x;
        Y = a2 + func_02052dc0(&it, i)->y;
        L[1] = 0xfff1;
        ok = (func_0204f538(obj, &L[1], X, Y, a3) == 0) ? 1 : 0;
        if (ok != 0) {
            func_02052e38(&it);
            return;
        }
        if (a6 != 0 && a3 == 0) {
            L[2] = 0xfff1;
            ok = (func_0204f538(obj, &L[2], X, Y, 1) == 0) ? 1 : 0;
            if (ok != 0) {
                func_02052e38(&it);
                return;
            }
        }
        func_02052ee8(X, Y, a3, a4, a0);
        if (a6 != 0 && a3 == 0) {
            func_02052ee8(X, Y, 1, a4, a0);
        }
        if (flag != 0 && a4 != 0) {
            func_02052e70(X, Y, a0);
        }
    }
    if (func_02073d90(data_020ccf94) != 0 && a7 != 0) {
        bf.b0 = a3;
        bf.b1 = a1;
        bf.b5 = a2;
        bf.b9 = a6;
        bf.b10 = a4;
        bf.b11 = L[0];
        g = data_020ccf94;
        func_02073820(g);
        func_020737f0(g, &bf, 4);
        func_02073770(g, 0x1b, 4);
    }
    func_02052e38(&it);
}
