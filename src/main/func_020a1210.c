/* func_020a1210 @ 0x020a1210, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_021f3c3c;

void func_020a1210(unsigned char r0)
{
    unsigned char *r1;

    r1 = data_021f3c3c;
    if (r1 != 0) {
        r1 += 0xf3;
        *r1 = r0;
    }
}
