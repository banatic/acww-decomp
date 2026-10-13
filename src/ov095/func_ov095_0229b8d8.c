/* func_ov095_0229b8d8 @ 0x0229b8d8, 0x108 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

int func_ov095_0229b8d8(int arg0, unsigned int b)
{
    switch (b - 0x3131) {
        case 0:
            return 0xac00;
        case 1:
            return 0xae4c;
        case 3:
            return 0xb098;
        case 6:
            return 0xb2e4;
        case 7:
            return 0xb530;
        case 8:
            return 0xb77c;
        case 16:
            return 0xb9c8;
        case 17:
            return 0xbc14;
        case 18:
            return 0xbe60;
        case 20:
            return 0xc0ac;
        case 21:
            return 0xc2f8;
        case 22:
            return 0xc544;
        case 23:
            return 0xc790;
        case 24:
            return 0xc9dc;
        case 25:
            return 0xcc28;
        case 26:
            return 0xce74;
        case 27:
            return 0xd0c0;
        case 28:
            return 0xd30c;
        case 29:
            return 0xd558;
        default:
            if (b < 0x314f) {
                return 0;
            }
            return (unsigned short) ((b - 0x314f) * 28);
    }
}
