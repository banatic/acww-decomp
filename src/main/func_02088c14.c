/* func_02088c14 @ 0x02088c14, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c8c9c;

int func_02088c14(unsigned int n)
{
    switch (n) {
        case 0:
            return 1;
        case 1:
            return 0;
        case 2:
            if (data_021c8c9c == 1) {
                return 1;
            } else {
                return 0;
            }
        case 3:
            if (data_021c8c9c == 0) {
                return 1;
            } else {
                return 0;
            }
        default:
            return 0;
    }
}
