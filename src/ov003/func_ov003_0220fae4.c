/* func_ov003_0220fae4 @ 0x0220fae4, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077978(const unsigned char *record, unsigned int *out, unsigned int *extra);

void func_ov003_0220fae4(unsigned char *r0, int r1, int r2, unsigned char *r3)
{
    unsigned char *r5 = r0;
    unsigned char *r4 = r3;
    unsigned char temp;

    func_02077978(r0, (unsigned int *) r1, (unsigned int *) r2);
    temp = r5[5];
    *r4 = temp;
}
