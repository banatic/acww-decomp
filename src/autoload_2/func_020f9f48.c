/* func_020f9f48 @ 0x020f9f48, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f9f48(void *r0);

int func_020f9f48(void *r0)
{
    int r2;
    unsigned char r1;

    r2 = -1;
    r1 = *(unsigned char *) ((char *) r0 + 8);
    if (r1 == 1) {
        r1 = *(unsigned char *) ((char *) r0 + 0xf);
        if (r1 == 0) {
            *(unsigned char *) ((char *) r0 + 0xf) = 1;
            r2 = 3;
        }
    }
    return r2;
}
