/* func_0208a9ac @ 0x0208a9ac, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208a9ac(void *r0);

void *func_0208a9ac(void *r0)
{
    unsigned char *r0_2;
    int r1;
    int r2;

    r1 = *(int *) ((char *) r0 + 0x34);
    if (r1 == 2) {
        r2 = 1;
    } else {
        r2 = 0;
    }

    if (r2 != 0) {
        r1 = 1;
        r0_2 = (unsigned char *) ((char *) r0 + 0x55);
        *r0_2 = (unsigned char) r1;
    }

    return (void *) (unsigned int) r2;
}
