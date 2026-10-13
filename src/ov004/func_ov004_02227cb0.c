/* func_ov004_02227cb0 @ 0x02227cb0, 0xb0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02227cb0 {
    int a;
    int b;
    int c;
};
extern void func_02010f5c(void *self);
extern void func_020eaca0(struct UnkStruct_02227cb0 *out, struct UnkStruct_02227cb0 *a, struct UnkStruct_02227cb0 *b);
extern int func_020ea9c8(struct UnkStruct_02227cb0 *v);
extern int FX_MulFunc(int a, int b);
extern void func_0200f95c(void *self);
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_02056f28(void *p, int k);
extern void func_0200f888(void *self);
void func_ov004_02227cb0(unsigned char *self)
{
    struct UnkStruct_02227cb0 v;
    int s, t;
    func_02010f5c(self);
    s = *(int *) (self + 0x704);
    if (s == 1) {
        func_020eaca0(&v, (struct UnkStruct_02227cb0 *) (self + 0x5c), (struct UnkStruct_02227cb0 *) (self + 0x68));
        t = FX_MulFunc(func_020ea9c8(&v), 0x3ae1) << 2;
        if (t <= *(int *) (self + 0x2d4)) {
            *(int *) (self + 0x2e0) = t;
        }
        func_0200f95c(self);
        if (t == 0) {
            func_020109fc(self, 0, 3, 0);
        }
    } else if (s != 0) {
        if (func_02056f28(self + 0x2d0, 1) != 0 || func_02056f28(self + 0x2d0, 6) != 0 ||
            func_02056f28(self + 0x2d0, 0xb) != 0 || func_02056f28(self + 0x2d0, 0x10) != 0) {
            func_0200f888(self);
        }
    }
}
