/* func_02017790 @ 0x02017790, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164cc(void *ptr, int);
extern void func_02057cb8(void *ptr);
extern void func_02016764(void *arg1, void *arg2, int arg3, unsigned short arg4, int arg5, int arg6, int arg7, int arg8);
extern void func_02019af0(void *arg1, int arg2);
extern unsigned short data_020c80f8;

void func_02017790(void *param0, void *param1)
{
    if (func_020164cc((char *) param1 + 0x334, (int) param1) != 0) {
        func_02057cb8(param1);
        func_02016764((char *) param1 + 0x334, param1, 0, data_020c80f8, 0, 0x1000, 0, 0);
        func_02019af0(param0, 1);
    }
}
