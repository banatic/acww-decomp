/* func_ov147_0229a3ac @ 0x0229a3ac, 0x38 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001e34(int, int);

void func_ov147_0229a3ac(void)
{
    volatile unsigned short *reg = (volatile unsigned short *) 0x0400000e;
    unsigned short val;

    val = *reg;
    val = (unsigned short) ((val & ~(unsigned short) 3) | 1);
    *reg = val;

    val = *reg;
    val = (unsigned short) ((val & 0x43) | 0x700);
    *reg = val;

    val = *reg;
    val = (unsigned short) (val & ~(unsigned short) 0x40);
    *reg = val;

    func_02001e34(0, 0);
}
