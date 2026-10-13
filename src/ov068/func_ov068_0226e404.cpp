/* func_ov068_0226e404 @ 0x0226e404, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226e404 {
  public:
    virtual void vfunc_00();
    char pad[0xac];
    int index;
    void method();
};

struct FlagEntry {
    unsigned char valid;
    char pad[11];
};

struct PMFEntry {
    void (UnkStruct_0226e404::*pmf)();
    char pad[4];
};

extern FlagEntry data_ov068_0227745c[];
extern PMFEntry data_ov068_02277454[];

extern "C" void func_ov068_0226e404(UnkStruct_0226e404 *self)
{
    int idx = self->index;
    if (data_ov068_0227745c[idx].valid == 0) {
        return;
    }
    PMFEntry &entry = data_ov068_02277454[idx];
    if (entry.pmf == 0) {
        return;
    }
    (self->*entry.pmf)();
}
