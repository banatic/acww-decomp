/* func_0204ba94 @ 0x0204ba94, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(void);

int func_0204ba94(void)
{
    int ret = 0;
    int x = func_0204b42c();

    switch (x) {
        case 0x26:
        case 0x2f:
        case 0x37:
        case 0x3f:
        case 0x47:
        case 0x4f:
        case 0x57:
        case 0x5d:
        case 0xc8:
            ret = 1;
            break;
        default:
            break;
    }

    return ret;
}
