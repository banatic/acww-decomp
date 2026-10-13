/* func_ov100_0229c2c0 @ 0x0229c2c0, 0x18 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

int func_ov100_0229c2c0(unsigned int *ptr, unsigned int mask)
{
    if (*(unsigned int *) ((char *) ptr + 0x28c0) & mask) {
        return 1;
    }
    return 0;
}
