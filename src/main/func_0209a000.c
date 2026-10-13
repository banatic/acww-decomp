/* func_0209a000 @ 0x0209a000, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099fe8(void);
extern void func_02061e2c(void *ptr, int a);
extern void func_0209a088(void *ptr, int b, int c);

int func_0209a000(int a, int b)
{
    int local[2];
    int result;

    result = func_02099fe8();
    if (result != -1) {
        func_02061e2c(local, a);
        func_0209a088(local, b, result);
        return 1;
    }
    return 0;
}
