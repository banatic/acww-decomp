/* func_ov112_0229fa2c @ 0x0229fa2c, 0x30 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

int func_ov112_0229fa2c(void *self)
{
    int a = data_021f6c58;
    int b = data_021f6c54;

    if (b - 8 < 0x10 || b - 8 > 0x38) {
        return 0;
    }
    if (a < 0xdd || a > 0xed) {
        return 0;
    }
    return 1;
}
