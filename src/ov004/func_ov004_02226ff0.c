/* func_ov004_02226ff0 @ 0x02226ff0, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_0200dc8c(void *self);
extern int func_0200dc48(void *self);
extern int func_02064558(short v);
extern void func_ov004_02228850(void *self, int a, int b);

void func_ov004_02226ff0(char *self)
{
    if (func_02056f94(self + 0x2d0) != 0) {
        if (func_0200dc8c(self) > 0) {
            if (func_02064558((short) (func_0200dc48(self) - *(short *) (self + 0x8e))) == 0) {
                func_ov004_02228850(self, 6, -1);
            }
        }
    }
}
