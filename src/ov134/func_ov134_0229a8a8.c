/* func_ov134_0229a8a8 @ 0x0229a8a8, 0x40 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229a96c(const unsigned char *p, int idx, int param);

void func_ov134_0229a8a8(unsigned char *p)
{
    int i;

    for (i = 0; i <= 5; i++) {
        if ((p + i)[0x98] != 0) {
            (p + i)[0x98]--;
            if ((p + i)[0x98] == 0) {
                func_ov134_0229a96c(p, i, 3);
            }
        }
    }
}
