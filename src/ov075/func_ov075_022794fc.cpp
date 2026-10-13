/* func_ov075_022794fc @ 0x022794fc, 0x4c bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022794fc_2;
typedef int (UnkStruct_022794fc_2::*PMF)();

struct UnkStruct_022794fc {
    int a;
    int b;
    PMF pmf;
};

extern UnkStruct_022794fc data_ov075_02279b10[];
extern UnkStruct_022794fc data_ov075_02279b08[];

struct UnkStruct_022794fc_2 {
    unsigned char pad_00[0x654];
    int index;
};

extern "C" int func_ov075_022794fc(UnkStruct_022794fc_2 *obj)
{
    int result = 0;
    if (data_ov075_02279b10[obj->index].a != 0) {
        result = (obj->*data_ov075_02279b08[obj->index].pmf)();
    }
    return result;
}
