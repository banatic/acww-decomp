/* func_02002d50 @ 0x02002d50, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02002d50(unsigned int param)
{
    switch (param) {
        case 3:
            return 1;
        case 0:
        case 4:
            return 2;
        case 1:
        case 5:
            return 4;
        case 2:
        case 6:
            return 8;
        case 7:
        case 8:
            return 16;
        default:
            return 1;
    }
}
