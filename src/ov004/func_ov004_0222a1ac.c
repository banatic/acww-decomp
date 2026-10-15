/* func_ov004_0222a1ac @ 0x0222a1ac, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

struct UnkStruct_0222a1ac {
    unsigned char unk_00;
    unsigned char unk_01;
};
extern int func_0200dc8c(void *self);
extern void func_020109fc(void *self, int a, int b, int c);
extern void *func_ov004_0222a220(void *p, int v);
extern void func_ov004_0222a218(void *p, int a, int b);
void func_ov004_0222a1ac(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_0222a1ac *q;
    unsigned char *w;
    int b0, b1, v;
    q = (struct UnkStruct_0222a1ac *) (p + 0xc);
    w = self + 0x7d4;
    b0 = *(unsigned char *) (p + 0xc);
    b1 = q->unk_01;
    v = func_0200dc8c(self);
    if (b0 != 0) {
        v = 0;
    }
    func_ov004_0222a220(w, v);
    if (b1 != 0) {
        func_020109fc(self, 0x1a, 3, 0);
    } else {
        func_020109fc(self, 0x1a, 0, 0);
    }
    func_ov004_0222a218(self + 0x8f0, b0, b1);
}
