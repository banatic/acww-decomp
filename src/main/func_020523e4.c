/* func_020523e4 @ 0x020523e4, 0x1c0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short x, y;
} Pt;

typedef struct {
    unsigned int b0 : 4;
    unsigned int b4 : 4;
    unsigned int b8 : 4;
    unsigned int b12 : 1;
    unsigned int b13 : 1;
    unsigned int b14 : 1;
    unsigned int b15 : 16;
} BF;

typedef struct {
    int unk_00, w1;
} It;

extern unsigned char data_020e54a8;
extern void *data_021c80bc;
extern void *data_020ccf94;
extern int func_020b65c4(void);
extern void *func_0204d5c8(int a);
extern int *func_02052e3c(It *it, unsigned short *src);
extern Pt *func_02052dc0(It *it, int i);
extern unsigned int func_02052e20(It *it);
extern void func_02052e38(It *it);
extern int func_0204f538(void *o, unsigned short *p, int x, int y, int q);
extern void func_02052ee8(int x, int y, int a, int b, int c);
extern int func_02052e98(int x, int y, int a, int b);
extern int func_02073d90(void *g);
extern void func_02073820(void *g);
extern void func_020737f0(void *g, void *p, int n);
extern void func_02073770(void *g, int off, int n);

void func_020523e4(int a0, int a1, int a2, int a3, int a4, int a5, int a6, unsigned short *a7, unsigned char a8)
{
    void *obj;
    int X, Y;
    unsigned short L[3];
    It it;
    BF bf;
    unsigned short *q;
    void *g;
    int i;
    unsigned int t;

    L[0] = *a7;
    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t > 0 && a0 == func_020b65c4()) {
        obj = data_021c80bc;
    } else {
        obj = func_0204d5c8(a0);
    }
    if (obj == 0) {
        return;
    }
    func_02052e3c(&it, a7);
    for (i = 0; i < func_02052e20(&it); i++) {
        X = a1 + func_02052dc0(&it, i)->x;
        Y = a2 + func_02052dc0(&it, i)->y;
        if (i == 0) {
            q = &L[0];
        } else {
            L[2] = 0xf031;
            q = &L[2];
        }
        L[1] = *q;
        if (func_0204f538(obj, &L[1], X, Y, a3) == 0) {
            func_02052e38(&it);
            return;
        }
        func_02052ee8(X, Y, a3, a4, a0);
        if (a5 != 0 && a4 != 0 && i == 0) {
            func_02052e98(X, Y, a6, a0);
        }
    }
    if (func_02073d90(data_020ccf94) != 0 && a8 != 0) {
        bf.b0 = a1;
        bf.b4 = a2;
        bf.b8 = a6 & 0xf;
        bf.b12 = a3;
        bf.b13 = a4;
        bf.b14 = a5;
        bf.b15 = L[0];
        g = data_020ccf94;
        func_02073820(g);
        func_020737f0(g, &bf, 4);
        func_02073770(g, 0x1c, 4);
    }
    func_02052e38(&it);
}
