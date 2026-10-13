/* func_ov003_0221f120 @ 0x0221f120, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c67a4;
extern void func_02055e7c(int a, int b);

int func_ov003_0221f120(int arg)
{
    if (data_021c67a4) {
        func_02055e7c(arg, 0);
        return 1;
    }
    return 0;
}
