/* func_02098ff8 @ 0x02098ff8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02098ff8(unsigned int *ptr, unsigned int bit)
{
    unsigned int word;
    unsigned int shift;
    word = bit >> 5;
    shift = bit & 0x1f;
    if ((int) word < 2) {
        unsigned int *base = (unsigned int *) ((char *) ptr + 0x23f8);
        ((volatile unsigned int *) base)[word] = (1 << shift) | ((volatile unsigned int *) base)[word];
    }
}
