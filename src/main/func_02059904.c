/* func_02059904 @ 0x02059904, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020cbae8;

void func_02059904(unsigned char *arg0, unsigned char arg1)
{
    unsigned char *r2;
    unsigned char *r0;
    unsigned char r1;

    r2 = arg0 + 0xda;
    *r2 = arg1;
    if (arg1 == 1 || arg1 == 7) {
        r1 = data_020cbae8;
        r0 = arg0 + 0xd5;
        *r0 = r1;
    }
}
