/* func_02053ea4 @ 0x02053ea4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206e73c(int a, int b, int c, int d, int e, int f, int g, int h);

extern unsigned char data_020dcfec[];
extern unsigned char data_020dd004[];
extern unsigned char data_020dd01c[];

int func_02053ea4(int a)
{
    return func_0206e73c(a, (unsigned int) data_020dcfec, 8, (unsigned int) data_020dd004, 4, (unsigned int) data_020dd01c,
                         0x20, 0x800);
}
