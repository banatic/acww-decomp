/* func_02066560 @ 0x02066560, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098844(int *ptr);
extern int func_02099870(int value);
extern void func_02065e60(int arg);
extern int func_020666d0(int arg1, int arg2);
extern int data_021dc7bc;

int func_02066560(int a0)
{
    int r4;
    r4 = func_02099870(func_02098844(&data_021dc7bc));
    func_02065e60(a0);
    return func_020666d0(a0 + 4, r4);
}
