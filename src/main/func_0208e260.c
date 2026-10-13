/* func_0208e260 @ 0x0208e260, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208e260(void *r0);

void *func_0208e260(void *r0)
{
    int r1;
    int r2;

    r1 = *(int *) ((char *) r0 + 0x70);
    if (r1 != 0) {
        r2 = 1;
    } else {
        r2 = 0;
    }
    if (r2 != 0) {
        *(int *) ((char *) r0 + 0x74) = 0;
    }
    return (void *) r2;
}
