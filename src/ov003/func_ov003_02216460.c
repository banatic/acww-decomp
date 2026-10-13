/* func_ov003_02216460 @ 0x02216460, 0xc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02216460(unsigned char *r0, unsigned char r1, unsigned int *r2);

void func_ov003_02216460(unsigned char *r0, unsigned char r1, unsigned int *r2)
{
    r0[2] = r1;
    r0[0] = (unsigned char) r2[0];
    r0[1] = (unsigned char) r2[1];
}
