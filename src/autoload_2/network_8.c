/* network_8: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020eb9c4 @ 0x020eb9c4, 0x2c bytes, ARM
 * func_020eb998 @ 0x020eb998, 0x2c bytes, ARM
 */

extern int func_ov066_02266c8c(void *p);
extern int func_ov066_02266cc8(int);

int func_020eb9c4(void *p)
{
    if (p == 0) {
        return 0;
    }
    return func_ov066_02266c8c(p);
}

int func_020eb998(int a)
{
    if (a == 0) {
        return 0;
    }
    return func_ov066_02266cc8(a);
}
