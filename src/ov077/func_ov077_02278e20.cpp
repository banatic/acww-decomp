/* func_ov077_02278e20 @ 0x02278e20, 0x50 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
void func_ov077_02278e10(void *self, int arg);
}

class UnkStruct_02278e20 {
  public:
    virtual void vf0();
    virtual void vf1();
    char pad_04[0xAC];
    int b0; // at 0xB0
};

typedef void (UnkStruct_02278e20::*PMF)();

struct PMFEntry {
    PMF pmf;   // 8 bytes
    int extra; // 4 bytes -> total 12
};

extern unsigned char data_ov077_022797d8[];
extern PMFEntry data_ov077_022797d0[];

extern "C" void func_ov077_02278e20(UnkStruct_02278e20 *self)
{
    int idx = self->b0;
    int off = idx * 12;
    if (data_ov077_022797d8[off] != 0) {
        return;
    }
    PMFEntry *e = (PMFEntry *) ((char *) data_ov077_022797d0 + off);
    if (e->pmf == 0) {
        return;
    }
    (self->*e->pmf)();
    func_ov077_02278e10(self, 0);
}
