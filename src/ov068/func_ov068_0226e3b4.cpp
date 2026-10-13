/* func_ov068_0226e3b4 @ 0x0226e3b4, 0x50 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226e3b4 {
  public:
    virtual void vfunc_00();
    char pad_04[0xb0 - 4];
    int unk_B0;
};

typedef void (UnkStruct_0226e3b4::*PMF)();

struct Entry {
    PMF pmf;
    unsigned char flag;
};

extern "C" void func_ov068_0226e3a4(UnkStruct_0226e3b4 *obj, int val);
extern Entry data_ov068_02277454[];

extern "C" void func_ov068_0226e3b4(UnkStruct_0226e3b4 *obj)
{
    int idx = obj->unk_B0;
    if (data_ov068_02277454[idx].flag != 0) {
        return;
    }
    if (data_ov068_02277454[idx].pmf == 0) {
        return;
    }
    (obj->*data_ov068_02277454[idx].pmf)();
    func_ov068_0226e3a4(obj, 0);
}
