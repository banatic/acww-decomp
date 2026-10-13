/* func_020a8328 @ 0x020a8328, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a87c8(int param1, int param2);

void func_020a8328(int *param0, int *param1, int *param2, int *param3)
{
    int temp;
    int val;
    int val2;

    temp = func_020a87c8(*(int *) (param0 + 3), 0);
    *param1 = temp;
    val = *(int *) (param0 + 3) + *(int *) (param0 + 2);
    *param2 = val;
    val2 = *(int *) (param0 + 3) + 1;
    *param3 = val2;
}
