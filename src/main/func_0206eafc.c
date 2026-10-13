/* func_0206eafc @ 0x0206eafc, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned char data_021cfc0c;

void func_0206eafc(unsigned int mask)
{
    volatile unsigned char *reg = &data_021cfc0c;
    *reg = (unsigned char) (*reg & ~mask);
}
