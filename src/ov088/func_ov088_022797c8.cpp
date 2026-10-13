/* func_ov088_022797c8 @ 0x022797c8, 0x4c bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022797c8;
typedef int (UnkStruct_022797c8::*PMF)();

struct PMFEntry {
    char pad_00[8];
    PMF pmf;
};

extern PMFEntry data_ov088_02279e28[];

struct UnkStruct_022797c8 {
    char pad_00[0x654];
    int index;
};

extern "C" int func_ov088_022797c8(UnkStruct_022797c8 *self)
{
    int index = self->index;
    int ret = 0;
    if (data_ov088_02279e28[index].pmf) {
        ret = (self->*data_ov088_02279e28[index].pmf)();
    }
    return ret;
}
