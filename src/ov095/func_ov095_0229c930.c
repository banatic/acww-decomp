/* func_ov095_0229c930 @ 0x0229c930, 0x44 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

int func_ov095_0229c930(unsigned char *p, int cmd, int sub)
{
    unsigned char val;
    switch (cmd) {
        case 0x109:
        case 0x10a:
            switch (sub) {
                case 0xC:
                    val = 0xC;
                    break;
                case 0xE:
                    val = 0xE;
                    break;
                case 0xD:
                    val = 0xD;
                    break;
            }
            if (cmd == 0x109) {
                p[0x19] = val;
            } else {
                p[0x1A] = val;
            }
            break;
        default:
            break;
    }
    return 0;
}
