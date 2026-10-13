/* func_ov106_0229ce38 @ 0x0229ce38, 0x2c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov106_0229ce38(unsigned char *self)
{
    unsigned int tmp;
    unsigned int tmp2;

    tmp = *(unsigned int *) (self + 0xa4);
    tmp += data_021f6c58;
    *(unsigned int *) (self + 0xac) = tmp;

    tmp2 = *(unsigned int *) (self + 0xa8);
    tmp2 += data_021f6c54;
    *(unsigned int *) (self + 0xb0) = tmp2;
}
