/* func_ov009_02263718 @ 0x02263718, 0x1a bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096174(void);
extern void func_ov009_022639a0(int, int);

void func_ov009_02263718(int param)
{
    int r4 = param;
    if (func_02096174() != 0) {
        func_ov009_022639a0(r4, 5);
    }
}
