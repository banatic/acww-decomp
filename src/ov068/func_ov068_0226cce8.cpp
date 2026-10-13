/* func_ov068_0226cce8 @ 0x0226cce8, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226cce8;

struct MFPEntry {
    void (UnkStruct_0226cce8::*pmf)(int);
    char pad_08[8];
};

extern "C" {
extern MFPEntry data_ov068_02278484[];
}

struct UnkStruct_0226cce8 {
    char pad_00[0x10];
    int idx;
    MFPEntry *entry;
    char pad_18[0x1c - 0x18];
    unsigned char flag;
};

extern "C" void func_ov068_0226cce8(UnkStruct_0226cce8 *self, int arg, int idx)
{
    if (idx < 0 || idx >= 0x18) {
        return;
    }
    self->idx = idx;
    self->entry = &data_ov068_02278484[self->idx];
    self->flag = 0;
    if (self->entry && self->entry->pmf) {
        (self->*self->entry->pmf)(arg);
    }
}
