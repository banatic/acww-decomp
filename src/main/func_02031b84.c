/* func_02031b84 @ 0x02031b84, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02031b84(void);
extern int func_01ffcb2c(void);

int func_02031b84(void)
{
    int result;
    int value;

    value = func_01ffcb2c();
    if (value == 3 || value == 0x1d) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
