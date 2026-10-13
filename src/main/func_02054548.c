/* func_02054548 @ 0x02054548, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned int func_02054548(unsigned int *base, unsigned int index)
{
    if (index >= 32) {
        if (*(unsigned int *) ((unsigned char *) base + 0x1b0) & (1 << (index - 32))) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*(unsigned int *) ((unsigned char *) base + 0x1ac) & (1 << index)) {
            return 1;
        } else {
            return 0;
        }
    }
}
