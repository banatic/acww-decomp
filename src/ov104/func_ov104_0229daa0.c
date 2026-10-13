/* func_ov104_0229daa0 @ 0x0229daa0, 0x38 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(const void *);

unsigned char func_ov104_0229daa0(unsigned char *base)
{
    unsigned char *p;
    int i;

    p = base + 0x2db4;
    for (i = 0; i < 10; i++) {
        if (func_02065ec0(p) == 0) {
            i += 0x15;
            return (unsigned char) i;
        }
        p += 0x100;
    }
    return 0x21;
}
