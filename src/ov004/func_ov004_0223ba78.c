/* func_ov004_0223ba78 @ 0x0223ba78, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int *func_ov004_0223ce84(void);
extern int func_ov004_0223cd58(int *a, unsigned int i);
extern int func_ov004_0223ba9c(int v);
int func_ov004_0223ba78(int i)
{
    if (i >= 0) {
        int v = func_ov004_0223cd58(func_ov004_0223ce84(), i);
        if (v != 0) {
            return func_ov004_0223ba9c(v);
        }
    }
    return 0;
}
