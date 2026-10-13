/* func_ov068_02274100 @ 0x02274100, 0x50 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov068_022740f8(void *, int);

class UnkStruct_02274100 {
  public:
    unsigned char pad[0xb8];
    int m_index;
};

typedef union {
    struct {
        int ptr;
        int adj;
    } raw;
    void (UnkStruct_02274100::*pmf)();
} PMFUnion;

typedef struct {
    PMFUnion pmf;
    int pad;
} PMFEntry;
typedef struct {
    unsigned char flag;
    unsigned char pad[11];
} FlagEntry;

extern "C" {
extern PMFEntry data_ov068_02277d70[];
extern FlagEntry data_ov068_02277d78[];
}

extern "C" void func_ov068_02274100(UnkStruct_02274100 *self)
{
    int idx = self->m_index;
    if (data_ov068_02277d78[idx].flag != 0) {
        return;
    }
    PMFEntry *entry = &data_ov068_02277d70[idx];
    if (entry->pmf.raw.ptr == 0) {
        return;
    }
    (self->*entry->pmf.pmf)();
    func_ov068_022740f8(self, 0);
}
