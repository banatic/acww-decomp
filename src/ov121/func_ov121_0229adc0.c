/* func_ov121_0229adc0 @ 0x0229adc0, 0x12 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov121_0229adc0(void *param0, int param1);

void func_ov121_0229adc0(void *param0, int param1)
{
    unsigned int *p;
    unsigned int r3;
    unsigned int r2;

    p = (unsigned int *) ((char *) param0 + 0x9c);
    r3 = *p;
    r2 = 1;
    r2 <<= param1;
    r3 |= r2;
    *((unsigned int *) ((char *) param0 + 0x9c)) = r3;
}
