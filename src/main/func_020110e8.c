/* func_020110e8 @ 0x020110e8, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011368(void *);
extern int func_0209984c(void *);
extern int func_0209975c(int);

int func_020110e8(void *argument0)
{
    int r4;
    int r5;

    r4 = func_02011368((void *) argument0);
    r5 = 0x20;
    if (r4 != 0) {
        r5 = func_0209984c((void *) r4);
        if (func_0209975c(r4) != 0) {
            r5 += 0x10;
        }
    }
    if (r5 < 0x20) {
        return r5;
    }
    return 0;
}
