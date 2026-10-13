/* func_020b025c @ 0x020b025c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f4acc;

void func_020b025c(unsigned char r0)
{
    unsigned char *ptr = &data_021f4acc;
    unsigned char value = *ptr;
    value &= ~r0;
    *ptr = value;
}
