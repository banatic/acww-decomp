/* func_ov079_02279c34 @ 0x02279c34, 0x44 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279c34 {
  public:
    virtual void vfunc_00() {}
    char pad[0x650];
    int unk_654;
};

typedef int (UnkStruct_02279c34::*PMF)();

struct Entry {
    union {
        struct {
            int func;
            int adj;
        } parts;
        PMF pmf;
    } u;
    int pad_08[2];
};

extern Entry data_ov079_0227a224[];

extern "C" void func_ov079_02279c34(UnkStruct_02279c34 *self, int idx)
{
    int r6 = 1;
    Entry *entry = &data_ov079_0227a224[idx];
    if (entry->u.parts.func != 0) {
        r6 = (self->*entry->u.pmf)();
    }
    if (r6 != 0) {
        self->unk_654 = idx;
    }
}
