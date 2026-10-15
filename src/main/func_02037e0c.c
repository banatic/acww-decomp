/* func_02037e0c @ 0x02037e0c, 0x38 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned int func_02037e0c(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3)
{
    unsigned int ip = 0;
    if (r3 < 2 && r1 < 0x10 && r2 < 0x10) {
        r0 = r0 + (r3 << 2);
        r3 = *(unsigned int *) (r0 + 0x18);
        if (r3 != 0) {
            r0 = r1 + (r2 << 4);
            ip = r3 + (r0 << 1);
        }
    }
    return ip;
}
