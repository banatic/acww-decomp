/* func_02055c40 @ 0x02055c40, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02055c40(void *arg0, unsigned int arg1);

unsigned int func_02055c40(void *arg0, unsigned int arg1)
{
    unsigned int r0;
    unsigned int r1;

    r0 = *(unsigned int *) ((char *) arg0 + 0xc);
    r0 &= 0xffff;
    r1 = arg1 >> 3;
    r1 <<= 0x10;
    r0 |= r1;
    return r0;
}
