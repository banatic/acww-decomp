/* func_ov068_02274150 @ 0x02274150, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02274150 {
    virtual void f0();
    char pad_04[0xb4];
    int unk_B8;
};

struct PMFEntry {
    int (UnkStruct_02274150::*pmf)();
    int pad_08;
};

extern unsigned char data_ov068_02277d78[];
extern PMFEntry data_ov068_02277d70[];

extern "C" void func_ov068_02274150(UnkStruct_02274150 *self)
{
    int offset = self->unk_B8 * 12;
    if (data_ov068_02277d78[offset]) {
        PMFEntry *entry = (PMFEntry *) ((char *) data_ov068_02277d70 + offset);
        if (entry->pmf) {
            (self->*entry->pmf)();
        }
    }
}
