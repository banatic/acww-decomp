/* func_ov003_02210114 @ 0x02210114, 0xc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02210114(void *r0, void *r1, unsigned char r2);

void func_ov003_02210114(void *r0, void *r1, unsigned char r2)
{
    unsigned char *dst = (unsigned char *) r0;
    unsigned int *src = (unsigned int *) r1;
    dst[0] = (unsigned char) src[0];
    dst[1] = (unsigned char) src[1];
    dst[2] = r2;
}
