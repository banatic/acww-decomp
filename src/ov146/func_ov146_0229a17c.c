/* func_ov146_0229a17c @ 0x0229a17c, 0x24 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov146_0229a1a0(unsigned char *p);

void func_ov146_0229a17c(unsigned char *p)
{
    if (p[0xb5] == 0) {
        func_ov146_0229a1a0(p);
        p[0xb5]++;
    }
}
