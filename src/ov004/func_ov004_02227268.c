/* func_ov004_02227268 @ 0x02227268, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02227268 {
    unsigned short a;
    unsigned short b;
};

extern int func_02056f94(void *p);
extern void func_ov004_02227210(void *self, int a, int b, int c, int d);
extern int func_020112e4(void *self);
extern void func_020112f8(unsigned short *p, void *self);
extern int func_020112d0(void *self);
extern int func_020100e8(void *self, struct UnkStruct_02227268 *t, int a, int b, int c);
extern int func_02011368(void *self);
extern void func_02099808(int a, int b);

void func_ov004_02227268(char *self)
{
    struct UnkStruct_02227268 t;
    unsigned char *q;

    if (func_02056f94(self + 0x2d0) != 0) {
        q = (unsigned char *) (self + 0x7d4);
        func_ov004_02227210(self, q[0], q[1], 6, -1);
        return;
    }
    if (((unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16) >= 3) {
        if (func_020112e4(self) != 0) {
            func_020112f8(&t.b, self);
            t.a = t.b;
            if (func_020100e8(self, &t, 0, func_020112d0(self), 0) != 0) {
                func_02099808(func_02011368(self), 0);
            }
        }
    }
}
