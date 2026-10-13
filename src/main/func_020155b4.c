/* func_020155b4 @ 0x020155b4, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020155b4(void *r0);

void *func_020155b4(void *r0)
{
    int r2;
    void *r1;

    r2 = 0;
    r1 = *(void **) ((char *) r0 + 0x40);
    if (r1 != 0) {
        if (*(int *) ((char *) r1 + 4) == 5) {
            r2 = 1;
            *(int *) ((char *) r1 + 8) = r2;
        }
    }
    return (void *) r2;
}
