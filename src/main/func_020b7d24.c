/* func_020b7d24 @ 0x020b7d24, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b7d24(void *r0, void *r1);

void *func_020b7d24(void *r0, void *r1)
{
    int r2;
    r2 = 0;
    *(int *) ((char *) r1 + 0x38) = r2;
    r2 = *(int *) ((char *) r0 + 0x1c);
    if (r2 == 0) {
        *(int *) ((char *) r0 + 0x1c) = (int) r1;
        return (void *) 1;
    }
    *(int *) ((char *) r1 + 0x38) = r2;
    *(int *) ((char *) r0 + 0x1c) = (int) r1;
    return (void *) 1;
}
