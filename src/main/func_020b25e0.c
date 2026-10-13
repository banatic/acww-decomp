/* func_020b25e0 @ 0x020b25e0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Nibble {
    unsigned char low : 4;
    unsigned char high : 4;
};

extern struct Nibble data_021f4bac[];

void func_020b25e0(unsigned char *idx, unsigned int bit)
{
    data_021f4bac[*idx].low &= ~(1 << bit);
}
