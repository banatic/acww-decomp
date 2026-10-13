/* func_02054580 @ 0x02054580, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02054580(unsigned int *base, unsigned int bit)
{
    if (bit >= 32) {
        *((unsigned int *) ((char *) base + 0x1b0)) &= ~(1u << (bit - 32));
    } else {
        *((unsigned int *) ((char *) base + 0x1ac)) &= ~(1u << bit);
    }
}
