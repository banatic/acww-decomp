/* func_02043a4c @ 0x02043a4c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02044858(int);
extern int func_02043cdc(int, int *, int);

int func_02043a4c(int a, int *b, int c)
{
    int tmp[2];
    int x;
    x = func_02044858(a);
    tmp[0] = b[0];
    tmp[1] = b[1];
    return func_02043cdc(x, tmp, c);
}
