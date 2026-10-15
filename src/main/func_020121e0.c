/* func_020121e0 @ 0x020121e0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_02082c98(char *arg);

char *func_020121e0(char *arg1, int arg2)
{
    char *p;
    p = func_02082c98(arg1 + 4);
    if (p) {
        *(int *) (p + 4) = arg2;
    }
    return p;
}
