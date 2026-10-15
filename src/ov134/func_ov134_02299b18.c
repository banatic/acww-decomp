/* func_ov134_02299b18 @ 0x02299b18, 0x24 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_02299b3c(void *unused0);

void func_ov134_02299b18(int *r0, int r1)
{
    r1 += r0[0x1a];
    r0[0x19] = r1;
    if (r0[0x19] < 0x20) {
        r0[0x19] = 0x20;
    }
    if (r0[0x19] > 0xa0) {
        r0[0x19] = 0xa0;
    }
    func_ov134_02299b3c(r0);
}
