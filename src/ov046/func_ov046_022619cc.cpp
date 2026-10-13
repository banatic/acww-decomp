/* func_ov046_022619cc @ 0x022619cc, 0x44 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022619cc;
typedef int (UnkStruct_022619cc::*PMF)();

class UnkStruct_022619cc {
  public:
    virtual int vfunc_00();
    char pad_04[0x650];
    int field_at_0x654;
};

struct TableEntry {
    PMF pmf;
    int pad_08;
    int pad_0C;
};

extern TableEntry data_ov046_0226248c[];

extern "C" void func_ov046_022619cc(UnkStruct_022619cc *obj, unsigned int idx)
{
    int ret = 1;
    if (data_ov046_0226248c[idx].pmf) {
        ret = (obj->*data_ov046_0226248c[idx].pmf)();
    }
    if (ret) {
        obj->field_at_0x654 = idx;
    }
}
