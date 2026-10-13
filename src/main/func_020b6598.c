/* func_020b6598 @ 0x020b6598, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020b65ac(unsigned int);

extern unsigned char data_021ebcc8[];

void func_020b6598(void)
{
    unsigned char *ptr;
    unsigned int value;

    ptr = (unsigned char *) data_021ebcc8;
    value = ptr[8];
    value = value << 0x18;
    value = value >> 0x1a;
    func_020b65ac(value);
}
