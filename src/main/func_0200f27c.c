/* func_0200f27c @ 0x0200f27c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *func_0200f27c(unsigned int *param0, int param1);

unsigned int *func_0200f27c(unsigned int *param0, int param1)
{
    unsigned int *r0;
    unsigned int r3;
    unsigned int r2;

    r0 = param0 + 0x1BB;
    r3 = *r0;
    r2 = 1;
    r2 = r2 << param1;
    r3 = r3 | r2;
    *r0 = r3;
    return r0;
}
