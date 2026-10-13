/* func_020ac318 @ 0x020ac318, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1dd4[];
extern unsigned char data_020d1dd8[];
extern unsigned char data_020d1ddc[];

int func_020ac318(int r0, int r1)
{
    int result;

    result = 0;
    if (r1 == 1) {
    } else if (r1 == 2) {
        result = data_020d1dd4[r0];
    } else if (r1 == 3) {
        result = data_020d1dd8[r0];
    } else if (r1 == 4) {
        result = data_020d1ddc[r0];
    } else if (r1 == 5) {
        result = r0;
    }
    return result * 26 + 153;
}
