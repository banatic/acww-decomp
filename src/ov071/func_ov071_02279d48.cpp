/* func_ov071_02279d48 @ 0x02279d48, 0x4c bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279d48;
struct CheckEntry {
    int a[4];
};
struct PMFEntry {
    int pad_00[2];
    int (UnkStruct_02279d48::*pmf)();
};
class UnkStruct_02279d48 {
  public:
    virtual void v0();
    virtual void v1();
};
extern CheckEntry data_ov071_0227a3ac[];
extern PMFEntry data_ov071_0227a3a4[];
extern "C" int func_ov071_02279d48(UnkStruct_02279d48 *self)
{
    int result = 0;
    int idx = *(int *) ((char *) self + 0x654);
    if (data_ov071_0227a3ac[idx].a[0] != 0) {
        result = (self->*data_ov071_0227a3a4[idx].pmf)();
    }
    return result;
}
