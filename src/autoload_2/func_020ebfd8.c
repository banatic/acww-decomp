/* func_020ebfd8 @ 0x020ebfd8, 0x68 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 *p;
    u32 unk_04;
} Str;

extern u32 DWC_GetAIDList(Str *s);
extern u8 DWC_GetMyAID(void);
extern int func_ov065_0227eef4(u8 c);

int func_020ebfd8(void)
{
    Str s;
    u32 i;
    u32 n;
    u8 c;

    n = DWC_GetAIDList(&s);
    for (i = 0; i < n; i++) {
        c = s.p[i];
        if (c != DWC_GetMyAID()) {
            if (func_ov065_0227eef4(c) == 0) {
                return 0;
            }
        }
    }
    return 1;
}
