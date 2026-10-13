/* func_0202ffe8 @ 0x0202ffe8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203002c(unsigned int *dest, unsigned int *ptr);

void func_0202ffe8(unsigned int *dest, const unsigned int *src1, const unsigned int *src2)
{
    dest[0] = src1[0];
    dest[1] = src1[1];
    dest[2] = src1[2];
    dest[3] = src2[0];
    dest[4] = src2[1];
    dest[5] = src2[2];
    func_0203002c(dest, dest + 6);
}
