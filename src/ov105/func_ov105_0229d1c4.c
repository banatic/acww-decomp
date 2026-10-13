/* func_ov105_0229d1c4 @ 0x0229d1c4, 0x2c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov105_0229d1c4(unsigned int *r0)
{
    unsigned int r2;
    unsigned int r1;

    r2 = *(unsigned int *) ((unsigned char *) r0 + 0xa4);
    r2 += data_021f6c58;
    *(unsigned int *) ((unsigned char *) r0 + 0xac) = r2;

    r2 = *(unsigned int *) ((unsigned char *) r0 + 0xa8);
    r1 = r2 + data_021f6c54;
    *(unsigned int *) ((unsigned char *) r0 + 0xb0) = r1;
}
