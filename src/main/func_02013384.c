/* func_02013384 @ 0x02013384, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02013384(unsigned char *r0, unsigned int *r1)
{
    unsigned char *p;
    int i;
    unsigned int a, b;

    p = r0 + 0x2c;
    i = 0;
    while (i < 0x1e) {
        a = *r1;
        b = *p;
        if (a == b) {
            a = *(r1 + 1);
            b = *(p + 1);
            if (a == b) {
                return i;
            }
        }
        p += 3;
        i++;
    }
    return -1;
}
