/* func_ov079_02279c78 @ 0x02279c78, 0x4c bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279c78;
struct CheckEntry {
    int a[4];
};
struct PMFEntry {
    int pad_00[2];
    int (UnkStruct_02279c78::*pmf)();
};
class UnkStruct_02279c78 {
  public:
    virtual void v0();
    virtual void v1();
};
extern CheckEntry data_ov079_0227a22c[];
extern PMFEntry data_ov079_0227a224[];
extern "C" int func_ov079_02279c78(UnkStruct_02279c78 *self)
{
    int result = 0;
    int idx = *(int *) ((char *) self + 0x654);
    if (data_ov079_0227a22c[idx].a[0] != 0) {
        result = (self->*data_ov079_0227a224[idx].pmf)();
    }
    return result;
}
