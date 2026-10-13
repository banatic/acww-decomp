/* func_ov004_02227038 @ 0x02227038, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02227038 {
    unsigned short a, b;
};

extern void func_02010f5c(void *self);
extern int func_02056f28(void *p, int a);
extern void func_02090c2c(int a, void *b, int c, int d);
extern void func_020112f8(unsigned short *p, void *self);
extern int func_020100e8(void *self, struct UnkStruct_02227038 *t, int a, int b, int c);
extern int func_02011368(void *self);
extern void func_02099808(int h, int a);
extern void func_020997e0(int h, int a);
extern int data_020e25d4;

void func_ov004_02227038(char *self)
{
    struct UnkStruct_02227038 t;
    unsigned char *q;
    int h;

    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 0xa) != 0) {
        func_02090c2c(0x60, self + 0x6e0, 0, (int) &data_020e25d4);
    }
    if (((unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16) >= 0xb) {
        q = (unsigned char *) (self + 0x7d4);
        if (q[2] == 0) {
            func_020112f8(&t.b, self);
            t.a = t.b;
            if (func_020100e8(self, &t, q[0], q[1], 0) != 0) {
                h = func_02011368(self);
                func_02099808(h, q[0]);
                func_020997e0(h, q[1]);
                q[2] = 1;
            }
        }
    }
}
