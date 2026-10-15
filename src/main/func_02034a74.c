/* func_02034a74 @ 0x02034a74, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off

extern unsigned char data_020e54a8;

extern void *func_ov004_022320ac(void);
extern int func_02034b04(int a, int b, int c, int d);

int func_02034a74(int param)
{
    int cond;

    cond = (data_020e54a8 == 1);
    if (cond) {
        func_02034b04((int) func_ov004_022320ac(), 0, 0, param);
        return 1;
    } else {
        return 0;
    }
}
