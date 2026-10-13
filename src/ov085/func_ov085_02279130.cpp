/* func_ov085_02279130 @ 0x02279130, 0x4c bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_02279130 {
  public:
    virtual void f();
};

struct Entry {
    int pad_00;
    int pad_04;
    int (UnkStruct_02279130::*pmf)();
};

extern Entry data_ov085_022795e0[];

int func_ov085_02279130(UnkStruct_02279130 *obj)
{
    int result = 0;
    int idx = *(int *) ((char *) obj + 0x654);
    if (data_ov085_022795e0[idx].pmf != 0) {
        result = (obj->*data_ov085_022795e0[idx].pmf)();
    }
    return result;
}
}
