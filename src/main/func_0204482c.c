/* func_0204482c @ 0x0204482c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int a);
extern int func_02073918(int a, int b);
extern int data_020ccf94;

int func_0204482c(int param)
{
    int a = data_020ccf94;
    if (func_02073d90(a) == 0) {
        return 1;
    } else {
        return func_02073918(a, param);
    }
}
