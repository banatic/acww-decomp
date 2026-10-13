/* func_ov004_02224978 @ 0x02224978, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019d0c(void *s, int kind, int value, int r3val, int argA, short argB, short argC, int argD, int argE,
                         unsigned short argF, unsigned short argG);
extern unsigned short data_020c80f8;

int func_ov004_02224978(char *self)
{
    *(int *) (self + 0x778) = 0;
    func_02019d0c((void *) (self + 0x564), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
