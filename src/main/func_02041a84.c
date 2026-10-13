/* func_02041a84 @ 0x02041a84, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02041a5c(void);
extern int func_020edf70(int);

void func_02041a84(void)
{
    int result;

    result = func_020edf70(0x9c);
    if (result != 0) {
        func_02041a5c();
    }
}
