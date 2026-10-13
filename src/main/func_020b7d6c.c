/* func_020b7d6c @ 0x020b7d6c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b7d6c(void *r0, void *r1);

void *func_020b7d6c(void *r0, void *r1)
{
    unsigned int *p0 = (unsigned int *) r0;
    unsigned int *p1 = (unsigned int *) r1;
    unsigned int *p2;

    p1[7] = 0;
    p2 = (unsigned int *) p0[9];
    if (p2 == 0) {
        p0[9] = (unsigned int) p1;
        return (void *) 1;
    }
    p1[7] = (unsigned int) p2;
    p0[9] = (unsigned int) p1;
    return (void *) 1;
}
