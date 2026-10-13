/* func_02079500 @ 0x02079500, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020794d8(unsigned char *p);

void func_02079500(unsigned char *p)
{
    switch (*p) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            if (func_020794d8(p) == 0) {
                *p = 1;
            } else {
                *p = 0;
            }
            break;
        default:
            break;
    }
}
