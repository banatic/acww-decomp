/* func_ov054_02261d10 @ 0x02261d10, 0x44 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261d10 {
  public:
    virtual ~UnkStruct_02261d10() {}
    char _pad[0xb8 - 4];
    int index;
};

struct PmfEntry {
    void (UnkStruct_02261d10::*pmf)();
    int extra;
};

struct FlagEntry {
    unsigned char valid;
    char pad_01[11];
};

extern PmfEntry data_ov054_02263140[];
extern FlagEntry data_ov054_02263148[];

extern "C" void func_ov054_02261d10(UnkStruct_02261d10 *self)
{
    int idx = self->index;
    if (data_ov054_02263148[idx].valid) {
        if (data_ov054_02263140[idx].pmf != 0) {
            (self->*data_ov054_02263140[idx].pmf)();
        }
    }
}
