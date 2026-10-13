/* func_ov003_0222eb94 @ 0x0222eb94, 0xe0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222eb94;
extern UnkStruct_0222eb94 *data_020ccf94;

extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);

int func_ov003_0222eb94(int a, char *self)
{
    u8 s;
    s8 k;

    s = *(u8 *) (self + 0x251);
    k = *(s8 *) (self + 0x24d);
    if (s != 9 && s != 0xb) {
        if (k == 0x3a || k == 0x3b || (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() == 0)) {
            return 0;
        }
        if (s != 7) {
            switch (k) {
                case 9:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 31:
                case 33:
                case 34:
                case 36:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 50:
                case 52:
                case 53:
                    return 0;
                case 0x33:
                    if (*(int *) (self + 0x220) != *(int *) (self + 0x228)) {
                        return 0;
                    }
                    break;
                case 0x31:
                    if (s == 6) {
                        return 0;
                    }
                    break;
            }
        }
    }
    return 1;
}
