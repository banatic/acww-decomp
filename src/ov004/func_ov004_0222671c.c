/* func_ov004_0222671c @ 0x0222671c, 0xec bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222671c {
    int a;
    int b;
    int c;
};
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_020b22a0(void);
extern int func_02073908(int a, int b);
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);
extern int func_0200f328(void *self, int msg);
extern void func_020b220c(void);
extern void func_ov004_02226818(void *dst, struct UnkStruct_0222671c v, int a, int b, unsigned char c);
extern void func_ov004_02226810(void *dst, int a, int c);
extern int data_020ccf94;
void func_ov004_0222671c(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_0222671c *q;
    struct UnkStruct_0222671c v;
    int msg, r;
    q = (struct UnkStruct_0222671c *) (p + 0xc);
    if (*(int *) (self + 0x704) != 1) {
        func_020109fc(self, 1, 3, 0);
    }
    msg = 0;
    r = func_020b22a0();
    switch (r) {
        case 2:
            msg = 0x4cb;
            break;
        case 1:
            msg = 0x4d2;
            break;
        case 0:
        case 3:
            if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
                func_020b6098(func_020b5e10(), *(int *) (self + 0x804));
            }
            break;
    }
    if (msg != 0) {
        if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
            func_0200f328(self, msg);
            if (msg == 0x4cb) {
                func_020b220c();
            }
        }
    }
    v.a = q->a;
    v.b = q->b;
    v.c = q->c;
    func_ov004_02226818(self + 0x7d4, v, *(int *) (self + 0x98), 0x400, (unsigned char) r);
    func_ov004_02226810(self + 0x8f0, v.a, v.c);
}
