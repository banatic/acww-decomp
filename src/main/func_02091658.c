/* func_02091658 @ 0x02091658, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094cf8(int, int, int, int, int, int);

void func_02091658(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = 0;
    func_02094cf8(0x15, r0, r1, r2, sp[0], sp[1]);
}
