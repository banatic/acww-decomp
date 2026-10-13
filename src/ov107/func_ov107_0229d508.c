/* func_ov107_0229d508 @ 0x0229d508, 0x26 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov107_0229cb3c(void *p);

void func_ov107_0229d508(unsigned char *p)
{
    if (p[0xbe] != 0) {
        p[0xbe]--;
    } else {
        func_ov107_0229cb3c(p);
    }
}
