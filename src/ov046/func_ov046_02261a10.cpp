/* func_ov046_02261a10 @ 0x02261a10, 0x4c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261a10 {
  public:
    virtual void vfunc();
    char pad_04[0x650];
    int unk_654;
};

typedef int (UnkStruct_02261a10::*Handler)();

struct Entry {
    int unk_00;
    int unk_04;
    Handler handler;
};

extern Entry data_ov046_02262494[];
extern Entry data_ov046_0226248c[];

extern "C" int func_ov046_02261a10(UnkStruct_02261a10 *self)
{
    int result = 0;
    int idx = self->unk_654;
    if (data_ov046_02262494[idx].unk_00 != 0) {
        result = (self->*data_ov046_0226248c[idx].handler)();
    }
    return result;
}
