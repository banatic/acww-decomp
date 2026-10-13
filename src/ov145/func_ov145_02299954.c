/* func_ov145_02299954 @ 0x02299954, 0x18 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

void func_ov145_02299954(unsigned char *p, unsigned char v)
{
    if (v != p[0xc1]) {
        p[0xc1] = v;
        p[0xc6] = 1;
    }
}
