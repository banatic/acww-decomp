/* func_ov004_0223badc @ 0x0223badc, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223ce84(void);
extern char *func_ov004_0223cd58(void *, int);
extern char data_ov004_0225967c[];

char *func_ov004_0223badc(int a)
{
    char *p = func_ov004_0223cd58(func_ov004_0223ce84(), a);
    if (p == 0) {
        return data_ov004_0225967c;
    }
    if (*(int *) (p + 0x150) < 0x4cd) {
        return data_ov004_0225967c;
    }
    return 0;
}
