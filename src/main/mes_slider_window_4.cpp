/* mes_slider_window_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020abe48 @ 0x020abe48, 0x34 bytes, Thumb
 * func_020abdc8 @ 0x020abdc8, 0x80 bytes, Thumb
 */

class UnkStruct_020abe48 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

struct Main {
    char pad_00[0x20];
    UnkStruct_020abe48 sub1;
    char pad_24[0x48];
    UnkStruct_020abe48 sub2;
    char pad_70[0x74];
    UnkStruct_020abe48 sub3;
    char pad_E8[0x5d];
    unsigned char flag;
};

class UnkStruct_020abdc8_2;

struct UnkStruct_020abdc8;

extern "C" void *func_0208f640(void *);
extern "C" int func_020b4980(void *, void *, int);
extern "C" void func_0208f218(UnkStruct_020abdc8_2 *, void *);
extern "C" void func_020aca94(UnkStruct_020abdc8_2 *, int);
extern "C" void func_020abcb4(struct UnkStruct_020abdc8 *);
extern "C" void *func_0208f628(void *);

class UnkStruct_020abdc8_2 {
  public:
    virtual void v0() {}
    virtual void v1() {}
    virtual void v2() {}
    virtual void v3() {}
    virtual void e(int x, int y);
};

struct UnkStruct_020abdc8 {
    char pad_00[0x18];
    short unk_18;
    short unk_1A;
    char pad_1C[0x20 - 0x1c];
    UnkStruct_020abdc8_2 obj_20;
    char pad_24[0x6c - (0x20 + 4)];
    UnkStruct_020abdc8_2 obj_6c;
    char pad_70[0xe4 - (0x6c + 4)];
    UnkStruct_020abdc8_2 obj_e4;
};

typedef struct {
    int data[9];
} UnkStruct_020abdc8_3;

extern "C" void func_020abe48(Main *self)
{
    if (self->flag) {
        self->sub1.f2();
    }
    self->sub2.f2();
    self->sub3.f2();
}

extern "C" void func_020abdc8(UnkStruct_020abdc8 *p)
{
    char byte;
    UnkStruct_020abdc8_3 local;
    int a = -p->unk_1A;
    int b = -p->unk_18;
    p->obj_20.e(b, a);
    p->obj_6c.e(0, a);
    p->obj_e4.e(b, a);
    func_0208f640(&local);
    byte = 0x12;
    func_020b4980(&local, &byte, 0);
    func_0208f218(&p->obj_6c, &local);
    func_020aca94(&p->obj_e4, 0x800);
    func_020abcb4(p);
    func_0208f628(&local);
}
