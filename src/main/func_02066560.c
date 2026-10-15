/* func_02066560 @ 0x02066560, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098844(int *ptr, int);
extern int func_02099870(int value);
extern void func_02065e60(int arg);
extern void func_020666d0(int arg1, int arg2);
extern int data_021dc7bc;

void func_02066560(int a0, int index)
{
    int r4;
    r4 = func_02099870(func_02098844(&data_021dc7bc, index));
    func_02065e60(a0);
    func_020666d0(a0 + 4, r4);
}
