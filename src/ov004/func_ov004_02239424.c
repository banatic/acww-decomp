/* func_ov004_02239424 @ 0x02239424, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ea9e4(int, int);
extern int func_0200322c(int, int);
extern void func_020e89dc(void *, int, int);

int func_ov004_02239424(void *a0, int a1, int a2, int a3)
{
    int r = 1;
    if (func_020ea9e4(a1, a2) > a3) {
        func_020e89dc(a0, func_0200322c(a1, a2), 0x38e);
        r = 0;
    }
    return r;
}
