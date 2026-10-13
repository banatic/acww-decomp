/* func_ov105_0229d78c @ 0x0229d78c, 0x48 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(void *ptr);

unsigned char func_ov105_0229d78c(void *self)
{
    unsigned char idx;
    unsigned char *p;
    int i;

    idx = ((unsigned char *) self)[0x2c0];
    p = (unsigned char *) self + 0x2db8 + ((idx * 25) << 8);
    for (i = 0; i < 25; i++) {
        if (func_02065ec0(p) == 0) {
            return (unsigned char) (i + 36);
        }
        p += 256;
    }
    return 64;
}
