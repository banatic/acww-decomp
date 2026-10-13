/* func_0203e2a8 @ 0x0203e2a8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021c72c0;

void func_0203e2a8(unsigned int r0)
{
    unsigned int r2;
    r2 = data_021c72c0;
    r2 &= ~r0;
    data_021c72c0 = r2;
}
