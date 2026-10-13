/* func_020349e8 @ 0x020349e8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021c519c[];
extern unsigned short data_021c5174[];

unsigned short *func_020349e8(unsigned int r0)
{
    unsigned short *result;

    if (r0 < 0x33) {
        result = &data_021c519c[r0];
    } else {
        result = data_021c5174;
    }
    return result;
}
