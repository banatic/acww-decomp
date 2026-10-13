/* func_ov003_02220b44 @ 0x02220b44, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204e414(void);
extern void func_0204f818(int *a, int *b, int param);
extern int func_0204eda8(void *handle, int a, int b);
extern int func_ov003_0222139c(void *data, int param, int *pair, int *zeros, int arg5, int arg6, int arg7, int arg8);

extern unsigned char data_ov003_0223cfe4[];

int func_ov003_02220b44(int param0, int param1)
{
    void *handle;
    int a, b;
    int pair[2];
    int zeros[3];
    int flag;

    handle = func_0204e414();
    if (handle == 0) {
        return 0;
    }

    a = 0;
    b = 0;
    func_0204f818(&a, &b, param1);
    flag = (func_0204eda8(handle, a, b) == 0) ? 0xfc : 0xfd;

    zeros[0] = 0;
    zeros[1] = 0;
    zeros[2] = 0;
    pair[0] = a;
    pair[1] = b;

    return func_ov003_0222139c((void *) data_ov003_0223cfe4, param0, pair, zeros, 14, flag, 0, 0);
}
