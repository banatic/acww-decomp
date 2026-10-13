/* func_02070a04 @ 0x02070a04, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_02051648(void *p);
extern "C" void func_02051694(void *p);

struct UnkStruct_02070a04 {
    unsigned char pad_00[0x10];
    int unk_10;
    unsigned char pad_14[0x1c];
    int unk_30;
    unsigned char pad_34[0x23];
    unsigned char unk_57;
};

class UnkStruct_02070a04_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
    unsigned char pad_04[0x64];
    UnkStruct_02070a04 *unk_68;
};

extern "C" void func_02070a04(UnkStruct_02070a04_2 *a, int b, int c)
{
    UnkStruct_02070a04 *p = a->unk_68;
    if (p) {
        p->unk_10 = a->f3();
        if (c) {
            a->unk_68->unk_57 = 1;
        } else {
            a->unk_68->unk_57 = 0;
        }
        if (b) {
            func_02051648(a->unk_68);
        } else {
            a->unk_68->unk_30 = 0;
        }
        func_02051694(a->unk_68);
    }
}
