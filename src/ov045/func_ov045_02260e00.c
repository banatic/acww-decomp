/* func_ov045_02260e00 @ 0x02260e00, 0x1c bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov045_02260644(void);
extern void func_0203e0a8(int, int);

int func_ov045_02260e00(int param)
{
    int r4 = param;
    if (func_ov045_02260644() != 0) {
        func_0203e0a8(r4, 0);
    }
    return 1;
}
