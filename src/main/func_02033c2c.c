/* func_02033c2c @ 0x02033c2c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(int, int, int, char *);
extern char func_02033ca8[];

int func_02033c2c(int a)
{
    __cxa_vec_cleanup(a, 0x28, 0x40, func_02033ca8);
    return a;
}
