/* func_0205f8b4 @ 0x0205f8b4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021cacec[];
extern unsigned long func_0205f8e0(unsigned char *ptr, unsigned char val);

unsigned long func_0205f8b4(unsigned char *p)
{
    return func_0205f8e0(data_021cacec, *p);
}
