/* func_ov003_02236164 @ 0x02236164, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 b0 : 6;
    u16 b6 : 1;
    u16 b7 : 9;
} Bits;
typedef struct UnkStruct_02236164 UnkStruct_02236164;
extern UnkStruct_02236164 *func_ov003_02236204(int idx);
UnkStruct_02236164 *func_ov003_02236164(int idx)
{
    UnkStruct_02236164 *o;
    o = func_ov003_02236204(idx & 1);
    if (o != 0 && *(int *) ((u8 *) o + 0x3a0) == 0 && *(int *) ((u8 *) o + 0x39c) == 0 &&
        (((Bits *) ((u8 *) o + 0x378))->b6 ? 1 : 0) == 0 && *((u8 *) o + 0x2e8) == 0) {
        return o;
    }
    return 0;
}
