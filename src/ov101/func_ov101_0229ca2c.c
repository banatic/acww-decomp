/* func_ov101_0229ca2c @ 0x0229ca2c, 0x2c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov101_0229ca2c(void *self)
{
    unsigned int tmp;
    unsigned int tmp2;

    tmp = *(unsigned int *) ((char *) self + 0x9c) + data_021f6c58;
    *(unsigned int *) ((char *) self + 0xa4) = tmp;

    tmp2 = *(unsigned int *) ((char *) self + 0xa0) + data_021f6c54;
    *(unsigned int *) ((char *) self + 0xa8) = tmp2;
}
