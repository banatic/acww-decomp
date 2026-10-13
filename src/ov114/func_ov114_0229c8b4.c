/* func_ov114_0229c8b4 @ 0x0229c8b4, 0x28 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_020019f4(int, int);

void func_ov114_0229c8b4(unsigned char *p)
{
    unsigned char v = p[0x12b8];
    p[0x12b9] = v;
    func_020019f4(0x12b9, v);
    p[0x12ba] = 0x10;
}
