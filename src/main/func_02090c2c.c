/* func_02090c2c @ 0x02090c2c, 0x124 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x20];
    s16 unk_20;
} UnkStruct_02090c2c;

typedef struct {
    u8 pad_00[8];
    UnkStruct_02090c2c *unk_08;
    u8 pad_0C[0x1c - 0xc];
    int unk_1C;
} UnkStruct_02090c2c_2;

typedef struct {
    u32 f0 : 1;
    u32 f1 : 1;
    u32 pad_flags : 30;
    int *unk_04;
    int count;
} TableEntry;

typedef struct {
    u8 pad_00[0x50];
    void *unk_50;
} Global;

extern Global *data_021d52c4;
extern TableEntry data_020d0f88[];
extern int data_021d52d4;

extern UnkStruct_02090c2c_2 *func_020902f8(void *sub_ptr, int val);
extern UnkStruct_02090c2c_2 *func_020fa0fc(void *f50, int val, int arg3_val);
extern int func_020902d0(void *sub_ptr, int val, UnkStruct_02090c2c_2 *obj);
extern void func_020fa090(void *f50, UnkStruct_02090c2c_2 *obj, int arg1);

int func_02090c2c(int id, int arg1, s16 *arg2, int *arg3)
{
    Global *glob;
    TableEntry *entry;
    int count;
    int *p4;
    int i;
    void *sub_ptr;
    UnkStruct_02090c2c_2 *obj;
    UnkStruct_02090c2c_2 *new_obj;
    int s_idx1;
    int s_idx2;
    UnkStruct_02090c2c *sub;

    if (arg1 == 0) {
        return 0;
    }

    glob = data_021d52c4;
    entry = &data_020d0f88[id];
    count = entry->count;
    p4 = entry->unk_04;

    if (arg2 != 0) {
        if (entry->f0 == 1) {
            count >>= 1;
            if (arg2[0] >= 0) {
                p4 += count;
            }
        }
    }

    data_021d52d4 = arg1;

    if (entry->f1 != 0) {
        sub_ptr = (char *) glob + 0x181c;
        i = 0;
        s_idx1 = 0;
        s_idx2 = 0;
        while (i < count) {
            obj = func_020902f8(sub_ptr, *p4);
            if (obj == 0) {
                new_obj = func_020fa0fc(data_021d52c4->unk_50, *p4, *arg3);
                if (new_obj != 0) {
                    if (func_020902d0(sub_ptr, *p4, new_obj) != 0) {
                        new_obj->unk_1C |= 2;
                        func_020fa090(data_021d52c4->unk_50, new_obj, arg1);
                        sub = new_obj->unk_08;
                        if (arg2 != 0) {
                            sub->unk_20 = arg2[s_idx2];
                        }
                    }
                }
            } else {
                func_020fa090(data_021d52c4->unk_50, obj, arg1);
                sub = obj->unk_08;
                if (arg2 != 0) {
                    sub->unk_20 = arg2[s_idx1];
                }
            }
            p4++;
            arg3++;
            i++;
        }
    } else {
        for (i = 0; i < count; i++) {
            func_020fa0fc(data_021d52c4->unk_50, *p4, *arg3);
            p4++;
            arg3++;
        }
    }

    data_021d52d4 = 0;
    return 1;
}
