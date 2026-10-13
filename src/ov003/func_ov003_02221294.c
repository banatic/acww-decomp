/* func_ov003_02221294 @ 0x02221294, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204e414(void);
extern void func_0204f818(int *a, int *b, int c);
extern int func_0204eda8(void *ctx, int a, int b);
extern int func_ov003_0222139c(int a0, int a1, int *a2, int *a3, int a4, int a5, int a6, int a7);
extern char data_ov003_0223cfe4[];

int func_ov003_02221294(int arg0, int arg1, int arg2)
{
    void *ctx;
    int a, b, flag;
    int pair[2];
    int triple[3];

    ctx = func_0204e414();
    if (ctx == 0) {
        return 0;
    }

    a = 0;
    b = 0;
    func_0204f818(&a, &b, arg1);

    flag = (func_0204eda8(ctx, a, b) == 0) ? 0xFC : 0xFD;

    triple[0] = 0;
    triple[1] = 0;
    triple[2] = 0;
    pair[0] = a;
    pair[1] = b;

    return func_ov003_0222139c((int) data_ov003_0223cfe4, arg0, pair, triple, 1, flag, 0, arg2);
}
