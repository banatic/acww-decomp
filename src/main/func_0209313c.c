/* func_0209313c @ 0x0209313c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02091494(int *, int, int, int, int, int, int);
extern int func_02090c2c(int, int, int, int *);
extern int data_021d5658;
extern int data_020e27c8;
extern int data_020e29fc;

int func_0209313c(int arg0, int arg1, int arg2, int arg3)
{
    int result = 3;
    func_02091494(&data_021d5658, -1, arg0, arg1, arg2, arg3, -1);
    if (func_02090c2c(0x76, arg1, arg2, &data_020e27c8) != 0 && func_02090c2c(0x54, arg1, arg2, &data_020e29fc) != 0) {
        result = 1;
    }
    return result;
}
