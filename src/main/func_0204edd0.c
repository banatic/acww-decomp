/* func_0204edd0 @ 0x0204edd0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02030e4c(int);
extern int func_02031a74(int, int);

int func_0204edd0(int arg0, int arg1, int arg2)
{
    int local_4;
    int result;

    result = ((int) (func_02030e4c(*(int *) (arg0 + 0x1c)), *(int *) (arg0 + 0x1c)));
    result = func_02031a74(arg1, arg2);
    func_02030e4c(0);
    return result;
}
