/* func_020883cc @ 0x020883cc, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099688(void);
extern int func_020882c4(void);
extern int func_020882dc(int);
extern int func_020e8b0c(int, int, int);

int func_020883cc(void)
{
    int r4;
    int result;

    if (func_020984e8() != 0) {
        r4 = func_02099688();
        if (func_020882c4() == 0) {
            result = func_020e8b0c(func_020882dc(r4), 1, 7);
            if (result != 0) {
                return 1;
            }
        }
    }
    return 0;
}
