/* func_0203c99c @ 0x0203c99c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203c97c(int a, void *b);
extern char data_020ca1ac[];

int func_0203c99c(int a, int b)
{
    return func_0203c97c(a, data_020ca1ac + (b << 4));
}
