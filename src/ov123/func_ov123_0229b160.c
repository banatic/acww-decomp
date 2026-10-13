/* func_ov123_0229b160 @ 0x0229b160, 0x12 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_0229b160(void *r0, unsigned char r1);

void func_ov123_0229b160(void *r0, unsigned char r1)
{
    ((unsigned char *) r0)[0xa2] = r1;
    ((unsigned char *) r0)[0xa3] = (r1 - 1) * 0xc;
}
