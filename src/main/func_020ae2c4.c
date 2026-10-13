/* func_020ae2c4 @ 0x020ae2c4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(int a);
extern int func_02099870(int a);
extern int func_02094ffc(int a);
extern int func_020ae4c8(void);
extern int func_0209871c(int *a, int b);
extern int func_020ae3b8(int *a, int b);
extern int func_020ae538(int a, int b);
extern int data_021dc7bc;
extern int data_021f3b30;

int func_020ae2c4(int x)
{
    int p;

    p = func_020984e8(x);
    if (p != 0) {
        p = func_02099870(p);
        if (func_02094ffc(p) == 1) {
            return func_020ae4c8();
        }
        p = (unsigned char) (func_0209871c(&data_021dc7bc, p) & 3);
        return func_020ae538(func_020ae3b8(&data_021f3b30, 3), p);
    } else {
        return 0;
    }
}
