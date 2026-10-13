/* func_02055c74 @ 0x02055c74, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02055c54(int *a, int b, int c);

int func_02055c74(int *a, int b)
{
    return func_02055c54(a, b, a[1]);
}
