/* func_020b1310 @ 0x020b1310, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_020b15b0(void);

void func_020b1310(void)
{
    unsigned short *ptr;
    unsigned short value;

    ptr = (unsigned short *) func_020b15b0();
    value = 0;
    ptr[0x251] = value;
}
