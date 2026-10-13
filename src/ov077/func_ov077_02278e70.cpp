/* func_ov077_02278e70 @ 0x02278e70, 0x44 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278e70 {
  public:
    char pad[0xB0];
    int idx;
};

typedef void (UnkStruct_02278e70::*PMF)();

struct FlagStruct {
    unsigned char flag;
    unsigned char pad[11];
};

struct PMFEntry {
    PMF pmf;
    int pad_08;
};

extern FlagStruct data_ov077_022797d8[];
extern PMFEntry data_ov077_022797d0[];

extern "C" void func_ov077_02278e70(UnkStruct_02278e70 *obj)
{
    int idx = obj->idx;
    if (data_ov077_022797d8[idx].flag) {
        if (data_ov077_022797d0[idx].pmf) {
            (obj->*data_ov077_022797d0[idx].pmf)();
        }
    }
}
