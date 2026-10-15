/* func_ov050_02262850 @ 0x02262850, 0x3c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209ad9c(int, int);
extern int func_0209b4d4(void *object);
extern void func_0209bb90(int, int);
extern int func_02099fe8(void);
extern void func_0206844c(int, int *, int);
extern int data_021f43e8;

void func_ov050_02262850(int param1, int param2)
{
    int res;

    res = func_0209ad9c(param2, 0);
    res = func_0209b4d4((void *) res);
    res = (func_0209bb90(res, 0), (int) res);
    if (func_02099fe8() >= 0) {
        *(int *) ((char *) param1 + 0xd0) = 0x25;
    } else {
        func_0206844c(*(int *) ((char *) param1 + 0x40), &data_021f43e8, 0);
    }
}
