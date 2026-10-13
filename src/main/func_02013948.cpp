/* func_02013948 @ 0x02013948, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int a;
    int b;
};
class UnkStruct_02013948 {
  public:
    virtual Pair method(void *, int);
};
struct Entry {
    char pad[8];
    Pair (UnkStruct_02013948::*pmf)(void *, int);
    char pad_10[0x30];
};
struct UnkStruct_02013948_2 {
    int unk_00, unk_04, unk_08;
    Pair pair;
    int unk_14, unk_18;
    char pad[0xc];
    Entry *unk_28;
};
extern Entry data_021c1914[];
extern "C" void func_020139bc(UnkStruct_02013948_2 *);
extern "C" void func_02012e58(UnkStruct_02013948_2 *, void *);
extern "C" void func_02013948(UnkStruct_02013948_2 *self, void *arg1, unsigned int index, int arg3, int arg5)
{
    if (index >= 7) {
        return;
    }
    func_020139bc(self);
    self->unk_08 = index;
    self->unk_00 = arg3;
    self->unk_28 = &data_021c1914[self->unk_08];
    if (self->unk_28->pmf != 0) {
        self->pair = (reinterpret_cast<UnkStruct_02013948 *>(self)->*self->unk_28->pmf)(arg1, arg5);
        int f10 = self->pair.b, fc = self->pair.a;
        self->unk_14 = fc >> 4;
        self->unk_18 = f10 >> 4;
        func_02012e58(self, arg1);
    }
}
