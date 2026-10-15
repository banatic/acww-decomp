/* func_ov147_02299b00 @ 0x02299b00, 0x44 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int *func_020682e0(int);
extern void func_02068320(void *);
extern void func_020a53ec(int value, int first, int second, int extra);
extern void func_ov147_0229a01c(void *);
extern unsigned char data_021c75b8;

void func_ov147_02299b00(void *arg)
{
    int *result;
    unsigned int cond;

    result = func_020682e0(0);
    cond = (data_021c75b8 == 2) ? 1 : 0;
    if (cond != 0) {
        if (result[1] == 0) {
            func_02068320(result);
            func_020a53ec(2, 2, 0, 0);
            func_ov147_0229a01c(arg);
        }
    }
}
