/* func_020f5134 @ 0x020f5134, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f5134(void *self);

int func_020f5134(void *self)
{
    int r2;
    unsigned char r1;
    unsigned char r0;

    r1 = *(unsigned char *) ((char *) self + 0x1b);
    r2 = 0;
    if (r1 == 0) {
        if (*(int *) ((char *) self + 8) != 0) {
            r2 = 1;
        }
        if (r2 != 0) {
            r0 = *(unsigned char *) ((char *) self + 0x1a);
            if (r0 != 0) {
                r2 = 0;
            } else {
                r2 = 1;
            }
        } else {
            r2 = 1;
        }
    }
    return r2;
}
