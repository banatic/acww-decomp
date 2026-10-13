/* func_020408b8 @ 0x020408b8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020408d4(void);

void func_020408b8(unsigned char *dest, unsigned char value, unsigned char *src)
{
    func_020408d4();
    dest[1] = src[4];
    dest[0] = src[3];
    dest[2] = value;
}
