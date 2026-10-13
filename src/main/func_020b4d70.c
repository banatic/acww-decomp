/* func_020b4d70 @ 0x020b4d70, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b4d70(int r0);

int func_020b4d70(int r0)
{
    int r2;
    int r1;

    r2 = 1;
    if (r0 == 0) {
        r2 = 0;
    }
    r1 = 0x0000ff10;
    if (r0 >= r1) {
        r1 = 0x0000ff19;
        if (r0 <= r1) {
            r2 = 0;
        }
    }
    r1 = 0x0000ff21;
    if (r0 >= r1) {
        r1 = 0x0000ff3a;
        if (r0 <= r1) {
            r2 = 0;
        }
    }
    r1 = 0x0000ff41;
    if (r0 >= r1) {
        r1 = 0x0000ff5a;
        if (r0 <= r1) {
            r2 = 0;
        }
    }
    return r2;
}
