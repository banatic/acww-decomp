/* func_ov066_022692c0 @ 0x022692c0, 0x60 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov066_02268024(unsigned char *p);
extern unsigned char *data_ov066_0226bdf4;

void func_ov066_022692c0(void)
{
    int i;
    unsigned char count = 0;
    int off;
    for (i = 0, off = 0; i < 16; i++, off += 6) {
        if (func_ov066_02268024(data_ov066_0226bdf4 + 0x28 + off) != 0) {
            count++;
        }
    }
    data_ov066_0226bdf4[0x8c] = count;
}
