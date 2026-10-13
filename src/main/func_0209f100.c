/* func_0209f100 @ 0x0209f100, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0209f100(unsigned int *ptr, unsigned int bit)
{
    unsigned int word;
    unsigned int shift;
    word = bit >> 5;
    shift = bit & 0x1f;
    if ((int) word < 1) {
        unsigned int *base = (unsigned int *) ((char *) ptr + 0x173f4);
        base[word] = ~(1 << shift) & ((volatile unsigned int *) base)[word];
    }
}
