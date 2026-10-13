/* func_02063bb4 @ 0x02063bb4, 0x6e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02063bb4(int month, unsigned int day)
{
    switch (month) {
        case 1:
            return 3;
        case 2:
            if (day > 0x18) {
                return 0;
            }
            return 3;
        case 3:
        case 4:
            return 0;
        case 5:
            if (day > 0x1a) {
                return 1;
            }
            return 0;
        case 6:
        case 7:
            return 1;
        case 8:
            if (day > 0x1a) {
                return 2;
            }
            return 1;
        case 9:
        case 10:
            return 2;
        case 11:
            if (day > 0x1a) {
                return 3;
            }
            return 2;
        case 0:
        default:
            return 3;
    }
}
