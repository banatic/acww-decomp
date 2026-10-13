/* func_ov099_0229c95c @ 0x0229c95c, 0x38 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov099_0229c95c(unsigned int *r0)
{
    unsigned int r2;
    unsigned char r1;

    r2 = r0[0x9fc];
    r1 = data_021f6c58;
    r2 += r1;
    r0[0x9fe] = r2;

    r2 = r0[0x9fd];
    r1 = data_021f6c54;
    r2 += r1;
    r0[0x9ff] = r2;
}
