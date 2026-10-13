/* func_ov004_0222fe50 @ 0x0222fe50, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8b0c(int a, int b, int c);
extern int func_02070070(void);
extern void func_ov004_0222c2c8(void *p, int k);

void func_ov004_0222fe50(void *self)
{
    unsigned int a = ((unsigned int) *(int *) ((char *) self + 0x334) << 4) >> 16;
    unsigned short b = (unsigned short) ((int) a / 0x38);

    if (func_020e8b0c((unsigned short) (a - b * 0x38), 0x11, 0x34) != 0 && func_02070070() == 0) {
        func_ov004_0222c2c8((char *) self + 0x250, 0x85e);
    }
}
