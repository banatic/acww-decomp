/* func_ov136_0229c58c @ 0x0229c58c, 0x9c bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);

extern u8 data_ov136_0229d41c[];
extern u8 data_ov136_0229d418[];
extern u8 data_ov136_0229d424[];
extern u8 data_ov136_0229d420[];

struct UnkStruct_0229c58c {
    u8 pad_00[0x2b77];
    u8 unk_2B77;
};

int func_ov136_0229c58c(struct UnkStruct_0229c58c *obj, int key)
{
    u8 orig = obj->unk_2B77;

    if (func_ov002_022088ac(key)) {
        obj->unk_2B77 = data_ov136_0229d41c[obj->unk_2B77];
    } else if (func_ov002_0220889c(key)) {
        obj->unk_2B77 = data_ov136_0229d418[obj->unk_2B77];
    }

    if (orig != obj->unk_2B77) {
        return 1;
    }

    if (func_ov002_022088cc(key)) {
        obj->unk_2B77 = data_ov136_0229d424[obj->unk_2B77];
    } else if (func_ov002_022088bc(key)) {
        obj->unk_2B77 = data_ov136_0229d420[obj->unk_2B77];
    }

    if (orig != obj->unk_2B77) {
        return 1;
    }

    return 0;
}
