/* func_02034a74 @ 0x02034a74, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;

extern int func_ov004_022320ac(int arg);
extern int func_02034b04(int a, int b, int c, int d);

int func_02034a74(int param)
{
    int cond;

    cond = (data_020e54a8 == 1);
    if (cond) {
        func_02034b04(func_ov004_022320ac(cond), 0, 0, param);
        return 1;
    } else {
        return 0;
    }
}
