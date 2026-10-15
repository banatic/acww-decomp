/* func_ov049_022627e4 @ 0x022627e4, 0x34 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(int a, int kind, int value, int r3val, int argA, short argB, short argC, int argD, int argE,
                         unsigned short argF, unsigned short argG);

int func_ov049_022627e4(int param)
{
    func_02019d0c(param + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
