/* rmo_telephone_6: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022315ec @ 0x022315ec, 0x26 bytes, Thumb
 * func_ov004_022315e4 @ 0x022315e4, 0x8 bytes, Thumb
 */

extern void func_ov004_0223121c(int a, int b);
extern char data_ov004_022478d0[];

void func_ov004_022315ec(int a, int b)
{
    switch (b) {
        case 0:
        case 1:
            func_ov004_0223121c(a, 1);
            break;
        case 8:
            func_ov004_0223121c(a, 0);
            break;
    }
}

void *func_ov004_022315e4(void)
{
    return data_ov004_022478d0;
}
