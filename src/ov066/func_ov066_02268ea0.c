/* func_ov066_02268ea0 @ 0x02268ea0, 0x34 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov066_0226bdec;
extern unsigned int data_ov066_0226bdf4;
extern void func_ov066_022686f0(void);

void func_ov066_02268ea0(unsigned short *param0)
{
    unsigned int *r1;
    unsigned int *r2;
    unsigned short *r0;

    r1 = (unsigned int *) &data_ov066_0226bdec;
    r2 = (unsigned int *) *r1;
    r2[1] = 9;
    r1 = (unsigned int *) &data_ov066_0226bdf4;
    r0 = (unsigned short *) *r1;
    r0[15] = param0[5];
    func_ov066_022686f0();
}
