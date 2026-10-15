/* func_ov004_02227d80 @ 0x02227d80, 0xfc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

struct UnkStruct_02227d80 {
    int a;
    int b;
    int c;
};
extern unsigned int *func_0200f27c(void *self, int a);
extern int func_020b5e10(void);
extern int func_020b5fc8(int h, int id, struct UnkStruct_02227d80 *v, struct UnkStruct_02227d80 *s);
extern int func_02064558(int a);
extern int func_0209d780(int id);
extern void func_ov004_02227e7c(void *w, int mode, int ang, int a, int c, int flag);
extern void func_020109a0(void *self, int a, int b, unsigned short d);
void func_ov004_02227d80(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_02227d80 v;
    unsigned char *w, *q;
    int mode, ang, flag;

    func_0200f27c(self, 3);
    q = p + 0xc;
    w = self + 0x7d4;
    func_020b5fc8(func_020b5e10(), *(int *) (self + 0x804), &v, (struct UnkStruct_02227d80 *) (self + 0x5c));
    mode = *(int *) (p + 0xc);
    ang = *(short *) (q + 4);
    if (mode == 2) {
        switch (func_02064558(ang)) {
            case 2:
                v.c = v.c + 0x1000;
                break;
            case 0:
                v.c = v.c - 0x1000;
                break;
            case 3:
                v.a = v.a + 0x1000;
                break;
            case 1:
                v.a = v.a - 0x1000;
                break;
        }
    } else if (mode == 0) {
        ang = -0x8000;
        v.a = *(int *) (self + 0x5c);
        v.c = *(int *) (self + 0x64);
    }
    flag = 0;
    if (func_0209d780(*(int *) (self + 0x804)) != 0) {
        flag = 1;
    }
    func_ov004_02227e7c(w, mode, ang, v.a, v.c, flag);
    if (flag == 0) {
        if (mode == 1) {
            func_020109a0(self, 0x3e, 3, 0);
        } else {
            func_020109a0(self, 0x3f, 3, 0);
        }
    } else {
        func_0200f27c(self, 0x18);
        func_020109a0(self, 1, 3, 0);
    }
}
