/* func_02011340 @ 0x02011340, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011368(void);
extern int func_02099870(void);
extern int func_020950c0(void);

int func_02011340(void)
{
    int r1;
    int r0;

    r0 = func_02011368();
    r1 = 0;
    if (r0 != 0) {
        func_02099870();
        r0 = func_020950c0();
        if (r0 != 0) {
            r1 = 1;
        } else {
            r1 = 0;
        }
    }
    return r1;
}
