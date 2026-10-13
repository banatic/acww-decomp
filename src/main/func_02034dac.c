/* func_02034dac @ 0x02034dac, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034d84(void);
extern int func_020edf70(int);

void func_02034dac(void)
{
    int result;

    result = func_020edf70(0x348);
    if (result != 0) {
        func_02034d84();
    }
}
