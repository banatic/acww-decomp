/* mes_choice_window_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ac278 @ 0x020ac278, 0x28 bytes, Thumb
 * func_020ac25c @ 0x020ac25c, 0x1c bytes, Thumb
 */

extern "C" void func_0208e594(void *obj, int a, int b);

class UnkStruct_020ac278_2 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

struct UnkStruct_020ac278 {
    char pad_00[0x1c];
    short unk_1C;
    char pad_1E[2];
    UnkStruct_020ac278_2 obj;
    char pad_24[0x48];
    int unk_6C;
};

class UnkStruct_020ac25c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

struct UnkStruct_020ac25c_2 {
    char pad_00[0x20];
    UnkStruct_020ac25c a;
    char pad_24[0x50];
    unsigned char flag;
};

extern "C" void func_020ac278(UnkStruct_020ac278 *s)
{
    func_0208e594(&s->obj, 5, s->unk_1C + ((s->unk_6C << 4) - 4));
    s->obj.vf3();
}

extern "C" void func_020ac25c(UnkStruct_020ac25c_2 *self)
{
    if (self->flag) {
        self->a.f2();
    }
}
