/* func_020f6d78 @ 0x020f6d78, 0x13c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[4];
    u8 *table;
    u8 pad_08[8];
    s8 state;
} Self2;

extern u8 data_02138fd4[13];

u8 func_020f6d78(Self2 *self, u8 idx)
{
    u8 result;
    s8 state = self->state;

    switch (state) {
        case 0:
            result = self->table[idx];
            goto end;
        case 1: {
            u8 rem = idx % 3;
            if (rem == 1) {
                result = 0xe;
            } else {
                u8 q = idx / 3;
                if (rem == 0) {
                    result = self->table[q * 2];
                } else {
                    result = self->table[q * 2 + 1];
                }
            }
            goto end;
        }
        case 2: {
            u8 rem = idx % 3;
            if (rem == 2) {
                result = 0xe;
            } else {
                u8 q = idx / 3;
                if (rem == 0) {
                    result = self->table[q * 2];
                } else {
                    result = self->table[q * 2 + 1];
                }
            }
            goto end;
        }
        case 3: {
            int found = 0;
            int i;
            u8 *p = data_02138fd4;
            for (i = 0; i < 13; i++) {
                if (idx == *p) {
                    result = self->table[i];
                    found = 1;
                }
                p++;
            }
            if (!found) {
                result = 0xe;
            }
            goto end;
        }
    }

end:
    return result;
}
