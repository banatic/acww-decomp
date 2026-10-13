/* func_ov134_02299980 @ 0x02299980, 0x2c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_02299710(unsigned char *p, int x);

void func_ov134_02299980(unsigned char *p, int x)
{
    if (p[0xB0] == 0) {
        return;
    }
    if (x < 0x28) {
        x = 0x28;
    } else if (x > 0xa8) {
        x = 0xa8;
    }
    p[0xB0] = func_ov134_02299710(p, x) + 1;
}
