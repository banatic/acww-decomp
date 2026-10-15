/* func_02019ac0 @ 0x02019ac0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020779b8(void *, int, int);
extern void MI_CpuCopy8(void *, void *, int);

void func_02019ac0(unsigned char *out, int x, int y, int z, int d, short e, unsigned short f)
{
    func_020779b8(out, x, y);
    func_020779b8(out + 5, z, d);
    MI_CpuCopy8(&e, out + 10, 2);
    out[12] = (unsigned char) f;
}
