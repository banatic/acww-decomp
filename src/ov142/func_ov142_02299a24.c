/* func_ov142_02299a24 @ 0x02299a24, 0x30 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fdd4(int, int, int, int, ...);
extern void func_ov142_02299658(int, int);

void func_ov142_02299a24(int r0, int r1)
{
    int sp[2];
    sp[0] = 0x13;
    sp[1] = r1;
    func_0206fdd4(r0 + 0x2860, 0x17, 4, 0x18, sp[0], sp[1]);
    func_ov142_02299658(r0, 0x10);
}
