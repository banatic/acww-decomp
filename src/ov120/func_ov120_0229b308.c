/* func_ov120_0229b308 @ 0x0229b308, 0x34 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229a448(char *p, int flag);
extern void func_ov120_0229b2b0(char *p, char *q);

void func_ov120_0229b308(char *p)
{
    if (func_ov120_0229a448(p, 1) != 0) {
        func_ov120_0229b2b0(p, p + 0x272d);
    } else {
        func_ov120_0229b2b0(p, p + 0x2720);
    }
}
