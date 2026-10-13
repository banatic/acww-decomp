/* func_ov004_0221f308 @ 0x0221f308, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_ov004_0221ef70(void *);

int func_ov004_0221f308(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_ov004_0221ef70(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}
