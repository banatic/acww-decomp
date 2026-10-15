/* func_ov073_02279070 @ 0x02279070, 0x50 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned short data_020c80f8;
extern int func_02019d0c(char *p, int kind, int value, int r3val, int argA, short argB, short argC, int argD, int argE,
                         unsigned short argF, unsigned short argG);
extern void func_02013c04(char *p);

int func_ov073_02279070(char *r4)
{
    func_02019d0c(r4 + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    *(r4 + 0x651) = 0;
    func_02013c04(r4 + 0x558);
    return 1;
}
