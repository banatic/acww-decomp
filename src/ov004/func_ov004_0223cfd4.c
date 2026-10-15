/* func_ov004_0223cfd4 @ 0x0223cfd4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223cfc4(void *arg0);
extern void func_0200440c(int);

void func_ov004_0223cfd4(int r0)
{
    int r4;
    int result;

    r4 = r0;
    result = func_ov004_0223cfc4((void *) r0);
    if (result != 0) {
        func_0200440c(r4);
    }
}
