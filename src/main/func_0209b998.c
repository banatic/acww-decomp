/* func_0209b998 @ 0x0209b998, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209b91c(void);
extern int func_0209bd44(void);
extern int func_0209bd04(int);
extern int func_0209bba0(int);
extern void func_0209bb90(int, int);

void func_0209b998(void)
{
    int r4;
    int r0;

    r4 = func_0209b91c();
    r0 = func_0209bd44();
    if (r0 != 0) {
        r0 = func_0209bd04(r4);
        if (r0 == 0) {
            r0 = func_0209bba0(r4);
            if (r0 == 1) {
                func_0209bb90(r4, 2);
            }
        }
    }
}
