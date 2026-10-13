/* func_02071628 @ 0x02071628, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(int);
extern int func_020996b8(int);
extern int func_02072bd0(int, int);

int func_02071628(int arg)
{
    int a = func_020984e8(arg);
    if (a != 0) {
        return func_02072bd0(func_020996b8(a), arg);
    }
    return 0;
}
