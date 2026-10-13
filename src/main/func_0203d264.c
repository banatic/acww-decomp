/* func_0203d264 @ 0x0203d264, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0203d264(unsigned char *ptr)
{
    unsigned int bit;
    bit = ((unsigned int) ptr[1] << 30) >> 31;
    if (bit == 0) {
        return 0;
    } else {
        return 1;
    }
}
