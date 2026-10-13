/* func_ov003_022350cc @ 0x022350cc, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_022350cc(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0:
        case 1:
            return 0x5000;
        case 2:
        case 3:
            return 0x4600;
        case 4:
            return 0x7800;
        case 5:
        case 6:
            return 0x5000;
        case 7:
            return 0xc800;
        case 0x25:
            return 0x3c00;
    }
    return 0;
}
