/* func_0201a698 @ 0x0201a698, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u8 unk_08;
    u8 unk_09;
} UnkStruct_0201a698_2;

typedef struct {
    u8 pad_00[0x20];
    u32 unk_20;
} UnkStruct_0201a698;

extern void func_0201a4e4(UnkStruct_0201a698 *out, u8 b);
extern void func_0201a6c8(UnkStruct_0201a698 *out, u32 a, u8 c, u32 d);

void func_0201a698(UnkStruct_0201a698 *out, UnkStruct_0201a698_2 *arr, int idx)
{
    UnkStruct_0201a698_2 *elem;

    elem = &arr[idx];

    if (elem->unk_09) {
        func_0201a4e4(out, elem->unk_09);
    }
    if (elem->unk_04) {
        func_0201a6c8(out, elem->unk_04, elem->unk_08, elem->unk_00);
        out->unk_20 = idx;
    }
}
