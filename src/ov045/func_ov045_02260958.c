/* func_ov045_02260958 @ 0x02260958, 0x1e bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035684(int, int, int);

void func_ov045_02260958(unsigned char *p)
{
    unsigned char v = p[0x1e];
    if (v == 0xe || v == 0x17) {
        func_02035684(0x10, 0, 0);
    }
}
