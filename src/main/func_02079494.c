/* func_02079494 @ 0x02079494, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02079494(void *r0);

void func_02079494(void *r0)
{
    unsigned short r1;
    r1 = *(unsigned short *) ((char *) r0 + 0x1a);
    if (r1 != 0) {
        r1 = r1 - 1;
        *(unsigned short *) ((char *) r0 + 0x1a) = r1;
    }
}
