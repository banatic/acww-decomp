/* func_ov003_022122fc @ 0x022122fc, 0xc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022122fc(unsigned char *r0, unsigned int *r1, unsigned char r2);

void func_ov003_022122fc(unsigned char *r0, unsigned int *r1, unsigned char r2)
{
    r0[0] = (unsigned char) r1[0];
    r0[1] = (unsigned char) r1[1];
    r0[2] = r2;
}
