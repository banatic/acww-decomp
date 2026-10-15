/* func_ov108_0229cbe4 @ 0x0229cbe4, 0x3c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229cd70(int unused0, unsigned unused1);
extern int func_ov108_0229cd5c(int, int);
extern int func_ov094_0229b328(int, int);

int func_ov108_0229cbe4(int r4, int r5)
{
    int r0;
    if (func_ov108_0229cd70(r4, r5)) {
        r0 = func_ov108_0229cd5c(r4, r5);
        r0 = func_ov094_0229b328(r4 + 0xd50, r0);
        r0 -= 0x10;
    } else {
        if (r5 == 0x15) {
            r0 = 0xb6;
        } else {
            r0 = 0;
        }
    }
    return r0;
}
