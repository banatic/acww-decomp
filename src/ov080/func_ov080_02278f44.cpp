/* func_ov080_02278f44 @ 0x02278f44, 0x4c bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_02278f44 {
  public:
    virtual void f();
};

struct Entry {
    int pad_00;
    int pad_04;
    int (UnkStruct_02278f44::*pmf)();
};

extern Entry data_ov080_022793e0[];

int func_ov080_02278f44(UnkStruct_02278f44 *obj)
{
    int result = 0;
    int idx = *(int *) ((char *) obj + 0x654);
    if (data_ov080_022793e0[idx].pmf != 0) {
        result = (obj->*data_ov080_022793e0[idx].pmf)();
    }
    return result;
}
}
