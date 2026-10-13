/* func_ov004_02227f24 @ 0x02227f24, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_02008258(void *self, int a);
extern void func_0200c3b0(void *self, int a, int b, int c);
extern void func_02057bb8(unsigned short *buf);
extern void func_02057cb8(void *self);

void func_ov004_02227f24(char *self)
{
    unsigned short buf[2];

    if (func_02056f94(self + 0x2d0) != 0) {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        func_0200c3b0(self, 3, 5, -1);
        func_02057bb8(buf);
        if (buf[0] == 0x1379) {
            *(char *) (self + 0x8eb) = 4;
        }
        func_02057cb8(self);
    }
}
