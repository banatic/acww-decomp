/* func_020f7d9c @ 0x020f7d9c, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

void func_020f7d9c(unsigned short *r4)
{
    extern void func_020f7bc4(void *r0, int r1, void *r2);
    unsigned short r0;

    func_020f7bc4(r4, 0x526, (void *) (r4 + 2));
    r0 = 0;
    *(unsigned short *) ((char *) r4 + 0x10) = r0;
    r0 = *(unsigned short *) ((char *) r4 + 0x10);
    *(unsigned short *) ((char *) r4 + 0xe) = r0;
}
