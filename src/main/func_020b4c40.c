/* func_020b4c40 @ 0x020b4c40, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a94a4(void *);

void func_020b4c40(void *r0)
{
    unsigned int *p = (unsigned int *) r0;
    unsigned char *b = (unsigned char *) r0;

    p[9] = 0;  // offset 0x24
    p[10] = 0; // offset 0x28
    p[11] = 0; // offset 0x2c
    p[12] = 0; // offset 0x30
    b[0x34] = 0;
    p[14] = 0; // offset 0x38
    p[15] = 0; // offset 0x3c

    func_020a94a4(r0);
}
