/* func_020fa0fc @ 0x020fa0fc, 0x94 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_020fa0fc {
    u32 x, y, z;
} UnkStruct_020fa0fc;
typedef struct Entry {
    u32 data[8];
} Entry;
typedef struct UnkStruct_020fa0fc_2 {
    u32 pad_00[6];
    u32 **unk_18;
} UnkStruct_020fa0fc_2;
typedef struct Parent {
    u32 pad_00;
    u32 unk_04;
    u32 pad_08;
    u32 unk_0C;
    u32 pad_10[3];
    Entry *unk_1C;
} Parent;

extern UnkStruct_020fa0fc_2 *func_020ff8a8(u32 *parent_field_c);
extern void func_020fb640(UnkStruct_020fa0fc_2 *obj, Entry *entry, UnkStruct_020fa0fc *local);
extern void func_020ff8ec(u32 *parent_field_4, UnkStruct_020fa0fc_2 *obj);

UnkStruct_020fa0fc_2 *func_020fa0fc(Parent *p, int idx, void (*cb)(UnkStruct_020fa0fc_2 *))
{
    UnkStruct_020fa0fc_2 *obj = 0;

    if (p->unk_0C != 0) {
        UnkStruct_020fa0fc local = {0, 0, 0};

        obj = func_020ff8a8(&p->unk_0C);
        func_020fb640(obj, &p->unk_1C[idx], &local);

        if (cb != 0) {
            cb(obj);
        }

        func_020ff8ec(&p->unk_04, obj);

        if (((**obj->unk_18 << 0x11) >> 0x1f) != 0) {
            obj = 0;
        }
    }

    return obj;
}
