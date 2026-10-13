/* func_ov113_02299d84 @ 0x02299d84, 0xe bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov113_02299d84(void *r0, unsigned short r1);

void func_ov113_02299d84(void *r0, unsigned short r1)
{
    unsigned short r2;
    r2 = *(unsigned short *) ((char *) r0 + 0x98);
    r2 &= ~r1;
    *(unsigned short *) ((char *) r0 + 0x98) = r2;
}
