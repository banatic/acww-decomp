/* func_ov147_0229a3e4 @ 0x0229a3e4, 0x20 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(unsigned int, unsigned int);
extern void func_02112ee8(unsigned int, unsigned int, unsigned int);

void func_ov147_0229a3e4(unsigned int a)
{
    DC_FlushRange(a, 0x800);
    func_02112ee8(a, 0, 0x800);
}
