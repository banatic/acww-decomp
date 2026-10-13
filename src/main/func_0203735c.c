/* func_0203735c @ 0x0203735c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203735c(void *arg0);

int func_0203735c(void *arg0)
{
    unsigned char r1;
    unsigned char r0;

    r1 = *(unsigned char *) ((char *) arg0 + 0x13);
    r0 = *(unsigned char *) ((char *) arg0 + 7);
    if (r1 != r0) {
        return 1;
    }
    return 0;
}
