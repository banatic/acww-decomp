/* func_ov094_02299f88 @ 0x02299f88, 0x30 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fdd4(int, int, int, int, int, int);
extern void func_ov094_022999a8(int, int);

void func_ov094_02299f88(int r4)
{
    int sp[2];
    sp[0] = 0xc;
    sp[1] = 2;
    func_0206fdd4(r4 + 0x1b8, 0xe, 3, 0x17, sp[0], sp[1]);
    func_ov094_022999a8(r4, 1);
}
