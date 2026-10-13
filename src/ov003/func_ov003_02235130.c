/* func_ov003_02235130 @ 0x02235130, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_02235130(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0:
        case 1:
        case 2:
        case 3:
            return 0xccd;
        case 4:
            return 0xb33;
        case 5:
            return 0xccd;
        case 6:
            return 0xb33;
        case 7:
        case 0x25:
            return 0xccd;
    }
    return 0;
}
