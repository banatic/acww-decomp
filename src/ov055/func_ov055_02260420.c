/* func_ov055_02260420 @ 0x02260420, 0x58 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090020(unsigned char *p);
extern void func_020901a0(unsigned char *p);
extern void func_ov055_02260a40(unsigned char *p);
extern void func_0202ee5c(unsigned char *p);
extern int data_ov055_02260fd4;

unsigned char *func_ov055_02260420(unsigned char *self)
{
    *(unsigned int *) self = (unsigned int) &data_ov055_02260fd4;
    func_02090020(self + 0x1abc);
    func_020901a0(self + 0x116c);
    func_02090020(self + 0x1064);
    func_020901a0(self + 0x714);
    func_ov055_02260a40(self + 0x658);
    func_0202ee5c(self);
    return self;
}
