/* func_0200c47c @ 0x0200c47c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020110a0(void *, short *);

void func_0200c47c(void *base)
{
    short local = *(short *) ((char *) base + 0x8e);
    short v2 = *(short *) ((char *) base + 0x7e2);
    if (local != 0) {
        int a = (local < 0) ? -local : local;
        int b = (v2 < 0) ? -v2 : v2;
        if (a < b) {
            local = 0;
        } else {
            local += v2;
        }
    }
    func_020110a0(base, &local);
}
