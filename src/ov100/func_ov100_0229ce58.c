/* func_ov100_0229ce58 @ 0x0229ce58, 0x38 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov100_0229ce58(unsigned int *r0)
{
    unsigned int r2;
    unsigned int r1;

    r2 = r0[0x28cc / 4];
    r1 = data_021f6c58;
    r2 += r1;
    r0[0x28d4 / 4] = r2;

    r2 = r0[0x28d0 / 4];
    r1 = data_021f6c54;
    r2 += r1;
    r0[0x28d8 / 4] = r2;
}
