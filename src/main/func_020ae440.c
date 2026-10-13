/* func_020ae440 @ 0x020ae440, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ae440(void *r0, int r1);

void func_020ae440(void *r0, int r1)
{
    unsigned int r4 = *(unsigned int *) r0;
    unsigned int r3 = 1;
    r3 <<= (r1 & 0x1f);
    r4 |= r3;
    *(unsigned int *) r0 = r4;
}
