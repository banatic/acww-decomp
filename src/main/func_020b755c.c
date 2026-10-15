/* func_020b755c @ 0x020b755c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020b8538(unsigned char);

unsigned char func_020b755c(void *r0, unsigned int *r1, unsigned int *r2, unsigned char *r3)
{
    unsigned char b;

    if (r1 != 0) {
        r1[0] = *(unsigned int *) ((char *) r0 + 0xc);
        r1[1] = *(unsigned int *) ((char *) r0 + 0x10);
        r1[2] = *(unsigned int *) ((char *) r0 + 0x14);
    }
    if (r2 != 0) {
        *r2 = *(unsigned char *) ((char *) r0 + 0x18);
    }
    if (r3 != 0) {
        *r3 = *(unsigned char *) ((char *) r0 + 0x19);
    }
    b = *(unsigned char *) ((char *) r0 + 0x18);
    return func_020b8538(b);
}
