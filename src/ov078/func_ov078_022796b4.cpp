/* func_ov078_022796b4 @ 0x022796b4, 0x4c bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_022796b4 {
  public:
    char pad[0x654];
    int index;
    int memberFunc();
};

typedef int (UnkStruct_022796b4::*PMF)();

struct CheckEntry {
    int flag;
    int pad[3];
};
struct PMFEntry {
    char pad[8];
    PMF pmf;
};

extern CheckEntry data_ov078_02279c50[];
extern PMFEntry data_ov078_02279c48[];

int func_ov078_022796b4(UnkStruct_022796b4 *obj)
{
    int result = 0;
    if (data_ov078_02279c50[obj->index].flag != 0) {
        result = (obj->*data_ov078_02279c48[obj->index].pmf)();
    }
    return result;
}
}
