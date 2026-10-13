/* func_ov094_0229b384 @ 0x0229b384, 0x6c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov094_0229c0ec[];

int func_ov094_0229b384(int arg0, int param)
{
    if (param >= 0 && param <= 9) {
        if (param & 1) {
            return 0xe4;
        } else {
            return 0xcc;
        }
    } else if (param >= 10 && param <= 34) {
        param -= 10;
        while (param >= 5) {
            param -= 5;
        }
        return data_ov094_0229c0ec[param];
    } else if (param >= 35 && param <= 44) {
        if ((param - 35) & 1) {
            return 0x84;
        } else {
            return 0x6c;
        }
    } else if (param >= 45 && param <= 54) {
        if ((param - 45) & 1) {
            return 0x84;
        } else {
            return 0x6c;
        }
    } else {
        return 0;
    }
}
