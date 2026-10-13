/* func_0203db44 @ 0x0203db44, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020a8354(void *addr);
extern "C" void func_020a9334(void *a, int b);
extern "C" void func_020a7994(void *addr, int val);

class Entry {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

struct This {
    char pad_00[0x24];
    unsigned char *unk_24;
    int unk_28;
    char pad_2C[0x20];
    unsigned int unk_4C;
};

extern "C" void func_0203db44(This *self)
{
    int idx = func_020a8354(&self->unk_28);
    Entry *entry = (Entry *) (self->unk_24 + 0x510 + idx * 0x5c);
    int v1 = entry->m3();
    func_020a9334(self, v1);
    int v2 = entry->m3();
    func_020a7994(self->unk_24 + 0x300, v2);
    *(unsigned int *) (self->unk_24 + 0x308) = 0;
    self->unk_4C = 0;
}
