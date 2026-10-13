/* func_020b25a8 @ 0x020b25a8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f4bac[];
extern unsigned char data_021f4bce[];
extern unsigned char data_021f4b14;

void func_020b25a8(void)
{
    unsigned char *p = data_021f4bac;

    while (p < data_021f4bce) {
        *p &= ~0xf;
        *p &= ~0xf0;
        p++;
    }

    data_021f4b14 = 0;
}
