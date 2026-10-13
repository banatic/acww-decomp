/* func_0202a12c @ 0x0202a12c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0202a12c(unsigned short *param0, int param1);

unsigned short func_0202a12c(unsigned short *param0, int param1)
{
    unsigned short result;
    int temp;
    unsigned short value;

    result = 0;
    temp = 0;
    value = *param0;
    if (value >= 0x12e8 && value <= 0x131f) {
        temp = 1;
    }
    if (temp != 0 && param1 == 0) {
        result = 1;
    }
    return result;
}
