/* func_ov053_02261484 @ 0x02261484, 0x2c bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov053_02260558(int);
extern int func_ov053_02260504(int);
extern int func_ov053_022604bc(int);

int func_ov053_02261484(int r0)
{
    int r4 = r0;
    if (func_ov053_02260558(r4) != 0) {
        return 1;
    }
    if (func_ov053_02260504(r4) != 0) {
        return 1;
    }
    func_ov053_022604bc(r4);
    return 1;
}
