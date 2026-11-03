/* snowman_7: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02236254 @ 0x02236254, 0x20 bytes, Thumb
 * func_ov003_02236230 @ 0x02236230, 0x24 bytes, Thumb
 * func_ov003_02236204 @ 0x02236204, 0x2c bytes, Thumb
 * func_ov003_022361bc @ 0x022361bc, 0x48 bytes, Thumb
 * func_ov003_02236164 @ 0x02236164, 0x58 bytes, Thumb
 * func_ov003_02236128 @ 0x02236128, 0x3c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    int id;
} UnkStruct_02236204;

typedef struct {
    u16 b0 : 6;
    u16 b6 : 1;
    u16 b7 : 9;
} Bits;

typedef struct UnkStruct_02236164 UnkStruct_02236164;

extern void *data_ov003_02262b38[8];
extern int func_ov003_0221a8e8(void *slot, void *a, int b, int c, int d, int e);
extern int func_ov003_0221a8d4(void *p);

int func_ov003_02236254(void *s)
{
    int i = *(int *) ((char *) s + 8) & 7;
    if (data_ov003_02262b38[i] != 0) {
        return 0;
    }
    data_ov003_02262b38[i] = s;
    return 1;
}

int func_ov003_02236230(void *o)
{
    int i = ((int *) o)[2] & 7;
    if (data_ov003_02262b38[i] == o) {
        data_ov003_02262b38[i] = 0;
        return 1;
    }
    return 0;
}

UnkStruct_02236204 *func_ov003_02236204(int id)
{
    unsigned int i;
    for (i = 0; i < 8; i++) {
        UnkStruct_02236204 *o = ((UnkStruct_02236204 * *) data_ov003_02262b38)[i];
        if (o != 0 && id == o->id) {
            return o;
        }
    }
    return 0;
}

int func_ov003_022361bc(void *a, int b, int c, int d, int e)
{
    unsigned int i;
    for (i = 0; i < 8; i++) {
        if (data_ov003_02262b38[i] != 0) {
            if (func_ov003_0221a8e8(data_ov003_02262b38[i], a, b, c, d, e)) {
                return 1;
            }
        }
    }
    return 0;
}

UnkStruct_02236164 *func_ov003_02236164(int idx)
{
    UnkStruct_02236164 *o;
    o = (UnkStruct_02236164 *) func_ov003_02236204(idx & 1);
    if (o != 0 && *(int *) ((u8 *) o + 0x3a0) == 0 && *(int *) ((u8 *) o + 0x39c) == 0 &&
        (((Bits *) ((u8 *) o + 0x378))->b6 ? 1 : 0) == 0 && *((u8 *) o + 0x2e8) == 0) {
        return o;
    }
    return 0;
}

void *func_ov003_02236128(void *self)
{
    unsigned int i;
    void *p;
    for (i = 0; i < 8; i++) {
        p = data_ov003_02262b38[i];
        if (p == 0) {
            continue;
        }
        if (p == self) {
            continue;
        }
        if (func_ov003_0221a8d4(p) == 0) {
            continue;
        }
        return p;
    }
    return 0;
}
