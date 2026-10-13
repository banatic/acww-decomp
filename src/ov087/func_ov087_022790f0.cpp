/* func_ov087_022790f0 @ 0x022790f0, 0x4c bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

extern "C" {

struct UnkStruct_022790f0 {
    char pad_00[0x654];
    int unk_654;
};

struct UnknownEntry {
    int flag;
    int pad_04;
    int (UnkStruct_022790f0::*pmf)();
};

extern UnknownEntry data_ov087_022795c8[];
extern UnknownEntry data_ov087_022795c0[];

int func_ov087_022790f0(UnkStruct_022790f0 *obj)
{
    int result = 0;
    int idx = obj->unk_654;
    if (data_ov087_022795c8[idx].flag != 0) {
        result = (obj->*data_ov087_022795c0[idx].pmf)();
    }
    return result;
}
}
