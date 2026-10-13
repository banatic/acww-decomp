/* func_ov146_02299838 @ 0x02299838, 0x24 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

void func_ov146_02299838(unsigned char *p)
{
    unsigned int v;
    p[0xB2] = 8;
    v = *(unsigned int *) (p + 0xA8) & 0xF;
    if (v != 0) {
        *(unsigned int *) (p + 0xA8) = *(unsigned int *) (p + 0xA8) - v;
    }
}
