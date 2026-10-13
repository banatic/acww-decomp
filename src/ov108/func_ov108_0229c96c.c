/* func_ov108_0229c96c @ 0x0229c96c, 0x2c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov108_0229c96c(unsigned int *self)
{
    unsigned int tmp;
    unsigned int tmp2;

    tmp = *(unsigned int *) ((char *) self + 0x9c);
    tmp += data_021f6c58;
    *(unsigned int *) ((char *) self + 0xa4) = tmp;

    tmp2 = *(unsigned int *) ((char *) self + 0xa0);
    tmp2 += data_021f6c54;
    *(unsigned int *) ((char *) self + 0xa8) = tmp2;
}
