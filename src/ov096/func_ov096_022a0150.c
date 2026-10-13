/* func_ov096_022a0150 @ 0x022a0150, 0x20 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229d268(int *param1);
extern int func_ov002_02208e18(int *param1);

void func_ov096_022a0150(int *param1)
{
    int *r4 = param1;
    if (func_ov002_02208e18(r4 + 0x959)) {
        func_ov096_0229d268(r4);
    }
}
