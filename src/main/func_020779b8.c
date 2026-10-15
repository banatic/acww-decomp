/* func_020779b8 @ 0x020779b8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077a14(unsigned char *, int, unsigned char);

void func_020779b8(unsigned char *ptr, int val, int other)
{
    *ptr = (unsigned char) (val >> 8);
    *(ptr + 1) = (unsigned char) val;
    ptr += 2;
    func_02077a14(ptr, other, (unsigned char) ((val >> 16) & 0xf));
}
