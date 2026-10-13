/* func_0206fee0 @ 0x0206fee0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfc6c;

void func_0206fee0(unsigned short r0)
{
    unsigned short r2;
    r2 = data_021cfc6c;
    r2 &= ~r0;
    data_021cfc6c = r2;
}
