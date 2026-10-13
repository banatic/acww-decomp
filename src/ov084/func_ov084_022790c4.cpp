/* func_ov084_022790c4 @ 0x022790c4, 0x4c bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022790c4 {
  public:
    char pad[0x654];
    int index;
    int method();
};

typedef int (UnkStruct_022790c4::*PMF)();

struct FlagEntry {
    int flag;
    char pad[12];
};

struct PMFContainer {
    char pad[8];
    PMF pmf;
};

extern FlagEntry data_ov084_022795a8[];
extern PMFContainer data_ov084_022795a0[];

extern "C" int func_ov084_022790c4(UnkStruct_022790c4 *obj)
{
    int ret = 0;
    int idx = obj->index;
    if (data_ov084_022795a8[idx].flag != 0) {
        ret = (obj->*data_ov084_022795a0[idx].pmf)();
    }
    return ret;
}
