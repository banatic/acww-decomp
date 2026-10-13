/* func_ov082_02279368 @ 0x02279368, 0x4c bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279368 {
  public:
    virtual int f0();
    virtual int f1();
};

typedef int (UnkStruct_02279368::*PMF)();

struct Entry {
    int pad_00;
    int pad_04;
    PMF pmf;
};

extern Entry data_ov082_02279914[];

extern "C" int func_ov082_02279368(UnkStruct_02279368 *self)
{
    int result = 0;
    int idx = *(int *) ((char *) self + 0x654);
    if (data_ov082_02279914[idx].pmf != 0) {
        result = (self->*data_ov082_02279914[idx].pmf)();
    }
    return result;
}
