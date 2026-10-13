/* func_0207ca74 @ 0x0207ca74, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200363c(int);

void func_0207ca74(unsigned int *bitset, int bit_index)
{
    int index;
    unsigned int word;

    if (func_0200363c(bit_index)) {
        index = bit_index >> 5;
        word = bitset[index];
        word |= (1u << (bit_index & 31));
        bitset[index] = word;
    }
}
