/* func_0202e9fc @ 0x0202e9fc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int);
extern int func_02073918(int, int);
extern int data_020ccf94;

int func_0202e9fc(void)
{
    int tmp = data_020ccf94;
    if (func_02073d90(tmp) != 0 && func_02073918(tmp, 0) == 0) {
        return 0;
    }
    return 1;
}
