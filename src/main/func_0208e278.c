/* func_0208e278 @ 0x0208e278, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e278(void *arg0);

int func_0208e278(void *arg0)
{
    int r2;
    int r1;

    r1 = *(int *) ((char *) arg0 + 0x70);
    if (r1 == 0) {
        r2 = 1;
    } else {
        r2 = 0;
    }
    if (r2 != 0) {
        *(int *) ((char *) arg0 + 0x74) = 2;
    }
    return r2;
}
