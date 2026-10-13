/* func_020346a4 @ 0x020346a4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020346a4(unsigned char *p)
{
    unsigned int i;
    for (i = 0; i < 4; i++) {
        if (((*p >> i) & 1) == 0) {
            return i;
        }
    }
    return -1;
}
