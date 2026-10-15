/* func_ov128_0229bae0 @ 0x0229bae0, 0x40 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

// Keypad decode: maps keys 0x20/0x10/0x40/0x80 to 0/1/3/2, default 4.

extern unsigned short data_021fbe40;

int func_ov128_0229bae0(void *receiver)
{
    int r = 4;
    unsigned short flags = data_021fbe40;
    if (flags & 0x20) {
        r = 0;
    } else if (flags & 0x10) {
        r = 1;
    } else if (flags & 0x40) {
        r = 3;
    } else if (flags & 0x80) {
        r = 2;
    }
    return r;
}
