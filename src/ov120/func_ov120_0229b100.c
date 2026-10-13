/* func_ov120_0229b100 @ 0x0229b100, 0x4c bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov120_0229adc4(void *ptr, unsigned char val);

int func_ov120_0229b100(void *ptr)
{
    unsigned char a = data_021f6c58;
    unsigned char b = data_021f6c54;
    if ((int) a < 0x98 || (int) a > 0xe8) {
        return 0;
    }
    if ((int) b < 0x50 || (int) b >= 0xb0) {
        return 0;
    }
    func_ov120_0229adc4(ptr, (unsigned char) (((b + (*(unsigned short *) ((char *) ptr + 0x98) - 0x50)) >> 4) + 0xf));
    return 1;
}
