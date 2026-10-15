/* func_ov003_022171ac @ 0x022171ac, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077978(const unsigned char *data, unsigned int *first, unsigned int *second);

void func_ov003_022171ac(const unsigned char *r0, unsigned int *r1, unsigned int *r2, unsigned char *r3)
{
    const unsigned char *r5 = r0;
    unsigned char *r4_ptr = r3;
    func_02077978(r0, r1, r2);
    *r4_ptr = r5[5];
}
