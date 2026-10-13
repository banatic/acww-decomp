/* func_020121c4 @ 0x020121c4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082c98(void *p);
extern int func_0205e8e4(int a);

int func_020121c4(char *p)
{
    int r = func_02082c98(p + 4);
    if (r) {
        return func_0205e8e4(r);
    }
    return 0;
}
