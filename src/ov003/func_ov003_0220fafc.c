/* func_ov003_0220fafc @ 0x0220fafc, 0x16 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020779b8(unsigned char *record, int value, int extra);

void func_ov003_0220fafc(int r0, int r1, int r2, int r3)
{
    int r5 = r0;
    int r4 = r3;
    func_020779b8((unsigned char *) r0, r1, r2);
    *(unsigned char *) (r5 + 5) = (unsigned char) r4;
}
