/* func_ov104_0229d554 @ 0x0229d554, 0x2c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov104_0229d554(unsigned int *param0)
{
    unsigned int *r1;
    unsigned int r2;
    unsigned char r3;

    r1 = (unsigned int *) ((char *) param0 + 0xa0);
    r2 = *r1;
    r3 = data_021f6c58;
    r2 += r3;
    r1 = (unsigned int *) ((char *) param0 + 0xa8);
    *r1 = r2;

    r1 = (unsigned int *) ((char *) param0 + 0xa4);
    r2 = *r1;
    r3 = data_021f6c54;
    r2 += r3;
    r1 = (unsigned int *) ((char *) param0 + 0xac);
    *r1 = r2;
}
