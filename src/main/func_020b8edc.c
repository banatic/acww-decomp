/* func_020b8edc @ 0x020b8edc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fce0(void);
extern int func_0206fd04(void);
extern int func_0206fd34(void);

int func_020b8edc(void)
{
    int a = func_0206fce0() != 0;
    int b = func_0206fd04() != 0;
    int c = func_0206fd34();
    if (a || (b && c < 0x1000)) {
        return 1;
    } else {
        return 0;
    }
}
