/* func_ov003_022171ac @ 0x022171ac, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077978(void);

void func_ov003_022171ac(int r0, int r1, int r2, unsigned char *r3, int r4)
{
    unsigned char *r5 = (unsigned char *) r0;
    unsigned char *r4_ptr = r3;
    func_02077978();
    *r4_ptr = r5[5];
}
