/* func_ov113_022999c4 @ 0x022999c4, 0x44 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov113_02299a08(void);
extern int func_ov113_02299da4(int, int);
extern int func_ov113_02299d84(int, int);

int func_ov113_022999c4(int param)
{
    int r4;
    int r5 = param;
    r4 = func_ov113_02299a08();
    if (func_ov113_02299da4(r5, 0x10) != 0) {
        r4 -= 0x100;
    } else if (func_ov113_02299da4(r5, 0x20) != 0) {
        r4 += 0x100;
    }
    func_ov113_02299d84(r5, 0x30);
    return r4;
}
