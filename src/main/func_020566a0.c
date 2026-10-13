/* func_020566a0 @ 0x020566a0, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02057a50(unsigned int);
extern int func_02057a40(unsigned int, int);
extern void func_02056968(void *, unsigned int, unsigned int);
struct UnkStruct_020566a0 {
    u8 pad_00[0x20];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 pad_23;
    u16 unk_24;
    u8 pad_26[2];
};
struct MainObj {
    u8 pad_00[0x18];
    unsigned int unk_18;
    unsigned int unk_1C;
    u8 pad_20[6];
    u8 count;
    u8 pad_27;
    struct UnkStruct_020566a0 *arr;
};
int func_020566a0(struct MainObj *obj, int unused, int param3)
{
    u8 c;
    int i;
    int res1;
    res1 = func_02057a50(obj->unk_18);
    if (res1 == (-1)) {
        return 0;
    }
    c = (u8) func_02057a40(obj->unk_1C, param3);
    if (c == (-1)) {
        return 0;
    }
    for (i = 0; i < obj->count; i++) {
        if (obj->arr[i].unk_22 == res1) {
            if (c != obj->arr[i].unk_20) {
                obj->arr[i].unk_20 = c;
                obj->arr[i].unk_21 = 0xff;
                obj->arr[i].unk_24 = 0xffff;
                func_02056968(&obj->arr[i], obj->unk_18, obj->unk_1C);
                return 1;
            } else {
                return 0;
            }
        }
    }

    return 0;
}
