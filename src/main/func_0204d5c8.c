/* func_0204d5c8 @ 0x0204d5c8, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void);
extern int func_020b67e8(void);
extern int func_0204df08(int);

int func_0204d5c8(int arg0)
{
    int r4;
    int r5;
    int result;

    r5 = arg0;
    r4 = 0;
    if (r5 == 0) {
        r4 = func_0204e414();
    } else {
        if (func_020b67e8() == 1) {
            r4 = func_0204df08(r5);
        }
    }
    return r4;
}
