/* func_ov083_02278e64 @ 0x02278e64, 0x34 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(char *ptr, int kind, int value, int r3val, int argA, short argB, short argC, int argD, int argE,
                         unsigned short argF, unsigned short argG);

int func_ov083_02278e64(char *self)
{

    func_02019d0c(self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
