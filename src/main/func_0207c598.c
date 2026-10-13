/* func_0207c598 @ 0x0207c598, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0207c818(void *p, unsigned char mask);
extern int func_0207c8c8(void *p, unsigned int index, int arg);

int func_0207c598(void *p)
{
    unsigned char mask = 0;
    int i;
    int a = 0;
    int b = 0;
    for (i = 0; i < 6; i++) {
        unsigned int result;
        int chk;
        result = func_0207c818(p, mask);
        if (result >= 6) {
            goto out;
        }
        chk = func_0207c8c8(p, result, a);
        if (chk != ~b) {
            return chk;
        }
        mask = (unsigned char) (mask | (1U << result));
    }
out:
    return -1;
}
