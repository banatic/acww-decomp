/* func_ov142_0229a0d4 @ 0x0229a0d4, 0x22 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209eec(void *);

int func_ov142_0229a0d4(void *arg)
{
    char *p = (char *) arg;
    if (func_ov002_02209eec(p + 0xe8) > 0x89) {
        p[0xc0] = 0x13;
        return 0x13;
    } else {
        p[0xc0] = 0x12;
        return 0x12;
    }
}
