/* func_020ebc30 @ 0x020ebc30, 0x288 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern int func_ov066_0226760c(void);

extern u8 data_021fbf68;

int func_020ebc30(void)
{
    int v;

    v = func_ov066_0226760c();
    if ((v & 0x80) != 0) {
        switch (v & ~0x80) {
            case 0:
                return 0;
            case 12:
                return 0x800c;
            case 1:
                return 0x8001;
            case 2:
                return 0x8002;
            case 3:
                return 0x8003;
            case 4:
                return 0x8004;
            case 5:
                return 0x8005;
            case 6:
                return 0x8006;
            case 7:
                return 0x8007;
            case 8:
                return 0x8008;
            case 9:
                return 0x8009;
            case 10:
                return 0x800a;
            case 11:
                return 0x800b;
            case 13:
                return 0x800d;
            case 14:
                return 0x800e;
            case 15:
                return 0x800f;
            case 16:
                return 0x8010;
            case 65:
                return 0x8041;
            case 66:
                return 0x8042;
            case 67:
                return 0x8043;
            case 68:
                return 0x8044;
            default:
                return 0xffff;
        }
    }
    if (data_021fbf68 == 0xff) {
        return 0x80ff;
    }
    return 0;
}
