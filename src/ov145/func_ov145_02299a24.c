/* func_ov145_02299a24 @ 0x02299a24, 0x10 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

short func_ov145_02299a24(unsigned char *arg0)
{
    unsigned char val;
    short val2;

    val = *(unsigned char *) (arg0 + 0xc0);
    val2 = *(short *) (arg0 + (val << 1) + 0xb8);
    return val2;
}
