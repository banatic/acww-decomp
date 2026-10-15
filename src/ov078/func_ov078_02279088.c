/* func_ov078_02279088 @ 0x02279088, 0x1c bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov078_0227952c(void *arg0);
extern void func_ov078_02279670(int, int);

int func_ov078_02279088(int param)
{
    if (func_ov078_0227952c((void *) param) != 0) {
        func_ov078_02279670(param, 2);
    }
    return 1;
}
