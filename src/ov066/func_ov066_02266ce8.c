/* func_ov066_02266ce8 @ 0x02266ce8, 0xd4 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct Ctl {
    unsigned char pad_00[4];
    u32 state; // 0x04
} Ctl;

extern Ctl *data_ov066_0226bdec;
int WM_GetLinkLevel(void);

int func_ov066_02266ce8(void)
{
    switch (data_ov066_0226bdec->state) {
        case 10:
        case 11:
            switch (WM_GetLinkLevel()) {
                case 0:
                    return 0;
                case 1:
                    return 1;
                case 2:
                    return 2;
                case 3:
                    return 3;
            }
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return 4;
    }
    return 5;
}
