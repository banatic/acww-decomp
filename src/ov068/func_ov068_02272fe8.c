/* func_ov068_02272fe8 @ 0x02272fe8, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02054ecc(int);
extern int func_ov004_0222c3c4(int, int);
extern void func_02055060(int, int, unsigned char, int, unsigned short, unsigned short);

void func_ov068_02272fe8(int unused, int p1, int p2, int p3, unsigned char p4, int p5, unsigned short p6, unsigned short p7)
{
    if (func_02054ecc(p2) != func_ov004_0222c3c4(p3, p1)) {
        func_02055060(p2, func_ov004_0222c3c4(p3, p1), p4, p5, p6, p7);
    }
}
