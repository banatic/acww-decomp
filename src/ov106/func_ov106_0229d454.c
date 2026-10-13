/* func_ov106_0229d454 @ 0x0229d454, 0x38 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(void *p);

int func_ov106_0229d454(void *base)
{
    char *p = (char *) base + 0x2bb4;
    int i;
    for (i = 0; i < 10; i++) {
        if (func_02065ec0(p)) {
            i += 0x15;
            return (unsigned char) i;
        }
        p += 0x100;
    }
    return 0x20;
}
