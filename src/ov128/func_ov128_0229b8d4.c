/* func_ov128_0229b8d4 @ 0x0229b8d4, 0x38 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov128_0229b90c(void);

void func_ov128_0229b8d4(void *r0)
{
    unsigned int r2;
    unsigned int r1;
    unsigned char r2b;

    r2 = *(unsigned int *) ((char *) r0 + 0x2d60);
    r1 = 0xffffffff;
    if (r2 != r1) {
        r1 = *(unsigned int *) ((char *) r0 + 0x2d64);
        if (r2 == r1) {
            func_ov128_0229b90c();
            return;
        }
    }
    r2b = 3;
    *(unsigned char *) ((char *) r0 + 0x2d6e) = r2b;
}
