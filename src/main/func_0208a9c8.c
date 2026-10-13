/* func_0208a9c8 @ 0x0208a9c8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208a9c8(void *arg0);

void *func_0208a9c8(void *arg0)
{
    unsigned char *ptr;
    int r2;
    int r1;

    r1 = *(int *) ((char *) arg0 + 0x34);
    if (r1 == 0) {
        r2 = 1;
    } else {
        r2 = 0;
    }
    if (r2 != 0) {
        r1 = 1;
        ptr = (unsigned char *) ((char *) arg0 + 0x54);
        *ptr = (unsigned char) r1;
    }
    return (void *) r2;
}
