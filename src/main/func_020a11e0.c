/* func_020a11e0 @ 0x020a11e0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_021f3c3c; // 0x021f3c3c

void func_020a11e0(unsigned char arg0)
{
    unsigned char *ptr;
    unsigned char *base;

    ptr = data_021f3c3c;
    if (ptr != 0) {
        base = ptr + 0x100;
        *base = arg0;
    }
}
