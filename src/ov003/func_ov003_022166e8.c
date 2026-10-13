/* func_ov003_022166e8 @ 0x022166e8, 0xe bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022166e8(unsigned char *r0, unsigned char r1, unsigned char r2, unsigned int *r3);

void func_ov003_022166e8(unsigned char *r0, unsigned char r1, unsigned char r2, unsigned int *r3)
{
    r0[2] = r1;
    r0[3] = r2;
    r0[0] = (unsigned char) (*r3);
    r0[1] = (unsigned char) (*(r3 + 1));
}
