/* func_02056a64 @ 0x02056a64, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02056a64(unsigned char *r0)
{
    unsigned char *r1;
    unsigned char r2;

    r2 = 0xff;
    r1 = r0 + 0x21;
    *r1 = r2;
    r1 = r0 + 0x22;
    *r1 = r2;
    r1 = r0 + 0x20;
    *r1 = r2;
    r2 = 0;
    r1 = r0 + 0x23;
    *r1 = r2;
    *(unsigned int *) r0 = r2;
    *(unsigned short *) (r0 + 0x24) = 0xffff;
}
