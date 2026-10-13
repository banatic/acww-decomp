/* func_ov003_02230cc0 @ 0x02230cc0, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int a);

short func_ov003_02230cc0(void)
{
    unsigned char v = (unsigned char) func_020644cc(0x10);
    int r = v;
    if (v > 8) {
        r = -(v - 8);
    }
    return (short) (0xaaa * r);
}
