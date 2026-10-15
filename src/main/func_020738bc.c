/* func_020738bc @ 0x020738bc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020738e4(int *);
extern int func_02077620(int);

int func_020738bc(int param1, int param2)
{
    int result;
    int temp;

    result = func_020738e4((int *) param1);
    if (result == 0) {
        return 0;
    }
    temp = func_02077620(param2);
    return result + temp;
}
