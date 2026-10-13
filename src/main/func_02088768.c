/* func_02088768 @ 0x02088768, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02088768(unsigned int *ptr, unsigned int bit)
{
    unsigned int word;
    unsigned int shift;
    word = bit >> 5;
    shift = bit & 0x1f;
    if ((int) word < 2) {
        unsigned int *base = (unsigned int *) ((char *) ptr + 4);
        base[word] = ~(1 << shift) & ((volatile unsigned int *) base)[word];
    }
}
