/* func_ov003_02210f3c @ 0x02210f3c, 0x14 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02210f3c(unsigned char *r0, unsigned char *r1, unsigned char *r2, unsigned char *r3);

void func_ov003_02210f3c(unsigned char *r0, unsigned char *r1, unsigned char *r2, unsigned char *r3)
{
    *r1 = *r0;
    *r2 = *(r0 + 1);
    *r3 = *(r0 + 2);
}
