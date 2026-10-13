/* func_ov004_02244ae4 @ 0x02244ae4, 0xfc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

int func_ov004_02244ae4(int kind, int variant)
{
    switch (kind) {
        case 10:
            return 0x831;
        case 51:
            return 0x823;
        case 29:
            return 0x825;
        case 27:
            return 0x826;
        case 28:
            return 0x82c;
        case 16:
            return 0x822;
        case 17:
            return 0x827;
        case 18:
            return 0x82e;
        case 19:
            return 0x824;
        case 50:
            return 0x828;
        case 30:
            if (variant == 0) {
                return 0x829;
            }
            return 0x82a;
        case 54:
            return 0x833;
        case 55:
            return 0x835;
        case 52:
            switch (variant) {
                case 0:
                    return 0x225;
                case 1:
                    return 0x226;
            }
            break;
    }
    return -1;
}
