/* func_ov076_022793b4 @ 0x022793b4, 0x4c bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022793b4 {
  public:
    virtual int vfunc();
    char pad_04[0x650];
    int unk_654;
};

typedef int (UnkStruct_022793b4::*Pmf)();

struct Entry {
    int unk_00;
    int unk_04;
    Pmf pmf;
};

extern Entry data_ov076_0227988c[];

extern "C" int func_ov076_022793b4(UnkStruct_022793b4 *obj)
{
    int ret = 0;
    int idx = obj->unk_654;
    if (data_ov076_0227988c[idx].pmf != 0) {
        ret = (obj->*data_ov076_0227988c[idx].pmf)();
    }
    return ret;
}
