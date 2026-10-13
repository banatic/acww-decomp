/* func_02002dc8 @ 0x02002dc8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02002dc8(unsigned int x)
{
    switch (x) {
        case 3:
            return 0;
        case 0:
        case 4:
            return 1;
        case 1:
        case 5:
            return 2;
        case 2:
        case 6:
            return 3;
        case 7:
        case 8:
            return 4;
        default:
            return 0;
    }
}
