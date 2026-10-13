/* func_ov003_02229874 @ 0x02229874, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x24c];
} UnkStruct_02229874;
extern UnkStruct_02229874 data_ov003_0225f76c[];

int func_ov003_02229874(char *self)
{
    int r = 0;
    s8 k;
    char *e;
    k = *(s8 *) (self + 0x78);
    if (k != -1) {
        e = (char *) &data_ov003_0225f76c[k];
        if (*(int *) (e + 0x22c) != 0) {
            *(int *) (e + 0x22c) = r;
        }
        *(s8 *) (e + 0x227) = -1;
        *(u8 *) (e + 0x23c) = 0;
        *(u8 *) (e + 0x224) = 0;
        r = 1;
    }
    return r;
}
