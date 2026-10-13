/* func_020356fc @ 0x020356fc, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ba4b8(void);
extern int func_020ba4c4(int *, int *);
extern int func_0200421c(int);

int func_020356fc(void)
{
    int r4;
    int r2;
    int r1;
    int r0;
    int sp0;
    int sp4;

    r4 = func_020ba4b8();
    func_020ba4c4(&sp0, &sp4);
    r0 = sp4;
    if (r0 < 3) {
        r2 = 0;
    } else {
        r2 = 1;
    }
    r1 = 0;
    if (r2 != 0) {
        if (r4 == 1) {
            r1 = 1;
        }
    }
    r0 = 0;
    if (r2 != 0) {
        if (r4 == 2) {
            r0 = 1;
        }
    }
    if (r1 != 0) {
        r0 = 0xc;
    } else {
        if (r0 != 0) {
            r0 = 0xd;
        } else {
            r0 = 0xb;
        }
    }
    return func_0200421c(r0);
}
