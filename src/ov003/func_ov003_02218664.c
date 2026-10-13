/* func_ov003_02218664 @ 0x02218664, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077978(void *a, int b, int c);
extern unsigned short func_020778f8(void *p);

void func_ov003_02218664(unsigned char *a0, unsigned char *a1, int a2, int a3, unsigned short *a4)
{
    *a1 = a0[7];
    func_02077978(a0, a2, a3);
    *a4 = func_020778f8(a0 + 5);
}
