/* func_ov120_0229a448 @ 0x0229a448, 0x12 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

int func_ov120_0229a448(void *self, unsigned short mask)
{
    unsigned short value;
    value = *(unsigned short *) ((char *) self + 0x9c);
    if ((value & mask) != 0) {
        return 1;
    }
    return 0;
}
