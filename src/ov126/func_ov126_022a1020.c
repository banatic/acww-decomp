/* func_ov126_022a1020 @ 0x022a1020, 0x18 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void);
extern void func_ov126_022a0bc8(int);

void func_ov126_022a1020(int r0)
{
    int r4 = r0;
    if (func_ov002_02208014() != 0) {
        func_ov126_022a0bc8(r4);
    }
}
