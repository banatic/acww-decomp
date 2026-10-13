/* func_020475b0 @ 0x020475b0, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_020475b0(int unused, unsigned short *p, int flag);

unsigned short func_020475b0(int unused, unsigned short *p, int flag)
{
    unsigned short result = 0xfff1;
    int r6 = 1;
    int r5 = r6;
    int r4 = r6;
    int r3 = 0;
    unsigned int val = *p;

    if (val >= 0x6eu && val <= 0x73u) {
        r3 = r6;
    }
    if (!r3 && (val < 0x74u || val > 0x79u)) {
        r4 = 0;
    }
    if (!r4 && (val < 0x7au || val > 0x7fu)) {
        r5 = 0;
    }
    if (!r5 && (val < 0x80u || val > 0x87u)) {
        r6 = 0;
    }

    if (r6) {
        if (val == 0x86u && flag != 0) {
            result = 0xa5;
        } else {
            result = (unsigned short) (val + 0x1cu);
        }
    } else {
        if (val == 0x88u) {
            result = 0xa4;
        } else if (val >= 0xd4u && val <= 0xdau) {
            result = (unsigned short) (val + 7u);
        }
    }

    return result;
}
