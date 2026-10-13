/* func_020c2868 @ 0x020c2868, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(int arg);
extern int func_020b65c4(int *ptr);
extern void func_0203e328(int val);
extern int data_021fbbe0;

int func_020c2868(int arg)
{
    int result;

    if (func_0202ec14(arg) == 0) {
        return 0;
    }
    data_021fbbe0 = 0;
    result = func_020b65c4(&data_021fbbe0);
    if (result == 0x2f) {
        func_0203e328(result);
    }
    return 1;
}
