/* func_02075f3c @ 0x02075f3c, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02090040(int);
extern int func_02090158(int);
extern int func_02075ff8(int, int, int, int, int);
extern int func_02073044(void);
extern int func_020ebf70(int);
extern int func_02077a8c(int);
extern int func_02073d28(int, int);
extern int func_02077b3c(int, int, int);
extern int func_02073e30(int, int, int, int, int, int, int, int, int, int);
extern int data_020ccf94;

int func_02075f3c(int param)
{
    int a, b, res1, res2;

    a = func_02090040(4);
    if (func_02090158(a) != 0) {
        return func_02075ff8(param, a, 0x950, 2, 1);
    }
    if (func_020ebf70(func_02073044()) && func_02077a8c(1)) {
        b = data_020ccf94;
        res1 = func_02073d28(b, 4);
        func_02077b3c(res1, 0, 2);
        res2 = func_02073d28(b, 4);
        return func_02073e30(b, res2, 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
