/* func_0206bba0 @ 0x0206bba0, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206ba6c(void *);

int func_0206bba0(void *r0)
{
    int r4 = 1;
    int r1 = *(int *) ((char *) r0 + 0x30);
    if (r1 == 2 || r1 == 5) {
        r4 = 0;
        *(int *) ((char *) r0 + 0x50) = 0;
        *(int *) ((char *) r0 + 0x54) = 0;
        *(int *) ((char *) r0 + 0x58) = 0;
    } else if (r1 == 4) {
        r4 = 0;
        *(int *) ((char *) r0 + 0x50) = 0;
        *(int *) ((char *) r0 + 0x54) = 0;
    } else if (r1 == 1) {
        if (func_0206ba6c(r0) == 0) {
            r4 = 0;
        }
    }
    return r4;
}
