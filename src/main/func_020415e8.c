/* func_020415e8 @ 0x020415e8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206e980(void);

extern unsigned char data_021c75a0[];

void func_020415e8(void)
{
    if (func_0206e980() != 0) {
        *((volatile unsigned char *) data_021c75a0) = 2;
    }
}
