/* func_ov112_0229fa5c @ 0x0229fa5c, 0x58 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_ov002_0220a58c(unsigned char *ptr, unsigned char a, unsigned char b);
extern int _s32_div_f(int a, int b);

int func_ov112_0229fa5c(unsigned char *self)
{
    if (func_ov002_0220a58c(self + 0x4234, data_021f6c58, data_021f6c54) != 0) {
        self[0xb9] = data_021f6c54;
        self[0xba] = (unsigned char) _s32_div_f(self[0xb6] << 1, 3);
        self[0xbb] = self[0xb6];
        return 1;
    }
    return 0;
}
