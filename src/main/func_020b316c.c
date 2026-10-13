/* func_020b316c @ 0x020b316c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f4bd0[34];
extern unsigned char data_021f4b14;

void func_020b316c(void)
{
    unsigned int i = 0;
    unsigned char val = i;
    for (; i < 0x22; i++) {
        data_021f4bd0[i] = val;
    }
    data_021f4b14 = val;
}
