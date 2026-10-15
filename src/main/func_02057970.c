/* func_02057970 @ 0x02057970, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020579b8(int, const char *name);
extern int func_02057988(int, int);

int func_02057970(int arg, const char *name)
{
    int tmp;
    tmp = func_020579b8(arg, name);
    return func_02057988(arg, tmp);
}
