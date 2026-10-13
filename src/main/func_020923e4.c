/* func_020923e4 @ 0x020923e4, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    char pad[4];
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_020923e4_2;

typedef struct {
    UnkStruct_020923e4_2 *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} Pointed;

typedef struct {
    char pad_00[0x18];
    Pointed *unk_18;
    char pad2[4];
    int unk_20;
    int unk_24;
    int unk_28;
    char pad_2C[0x10];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
} UnkStruct_020923e4_3;

typedef struct {
    char pad[4];
    u8 raw[4];
    char pad2[4];
    UnkStruct_020923e4_3 *unk_0C;
} UnkStruct_020923e4;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad[2];
    short unk_0E;
    char pad2[2];
    int unk_14;
    int unk_18;
} TableEntry;

extern TableEntry data_021d52d8[];
extern void func_020914dc(void *entry);

int func_020923e4(UnkStruct_020923e4 *self)
{
    u8 buf[4];
    u8 *p;
    u8 *q;
    int count;
    int flag;
    UnkStruct_020923e4_3 *inner;
    TableEntry *entry;

    p = (u8 *) self + 4;
    q = buf;
    count = 4;
    do {
        *q++ = *p++;
        count--;
    } while (count != 0);
    entry = &data_021d52d8[buf[0]];
    flag = 0;
    if (entry->unk_14 != -1) {
        if ((s16) entry->unk_0E != 0) {
            inner = self->unk_0C;
            inner->unk_20 = entry->unk_00 + inner->unk_18->unk_00->unk_04;
            inner->unk_24 = entry->unk_04 + inner->unk_18->unk_00->unk_08;
            inner->unk_28 = entry->unk_08 + inner->unk_18->unk_00->unk_0C;
            if ((s16) entry->unk_0E > 0) {
                *(u8 *) ((char *) self->unk_0C + 0x69) = (s16) entry->unk_0E * 0x2955 >> 12;
                entry->unk_0E = (s16) entry->unk_0E - 1;
            }
            flag = 1;
        }
    }
    if (flag == 0) {
        func_020914dc(entry);
    }
    return flag;
}
