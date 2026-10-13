/* func_ov004_022387b0 @ 0x022387b0, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov004_022593ac;
extern void func_0200430c(void *p);

void func_ov004_022387b0(void *self)
{
    *((char *) self + 0x1c7) = 0;
    *(int *) ((char *) self + 0x1a8) = 0x14500;
    *(int *) ((char *) self + 0x1ac) = 0x3700;
    *(int *) ((char *) self + 0x1b0) = 0x15400;
    *(short *) ((char *) self + 0x1c0) = 0;
    data_ov004_022593ac = self;
    func_0200430c((char *) self + 0x1fc);
}
