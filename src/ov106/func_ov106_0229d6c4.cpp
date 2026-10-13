/* func_ov106_0229d6c4 @ 0x0229d6c4, 0x60 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov106_0229d6c4(void *p);

extern "C" void func_ov002_02207fc0(void *);
extern "C" void func_ov002_0220a374(void *, int);
extern "C" int func_ov002_0220a768(void *, int);
extern "C" int func_ov002_0220a72c(void *, int);
extern "C" void func_ov002_0220a0b4(void *, int, int);
extern "C" void func_ov002_02208098(void *, int);

class UnkStruct_0229d6c4 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct Big {
    char pad_00[0xbe];
    char flag;
    char pad_BF[0x22a0 - 0xbf];
    UnkStruct_0229d6c4 sub1;
    char pad2[0x3fb4 - (0x22a0 + sizeof(UnkStruct_0229d6c4))];
    int unk_3FB4;
};

void func_ov106_0229d6c4(void *p)
{
    Big *o = (Big *) p;
    func_ov002_02207fc0(o);
    o->flag = 1;
    func_ov002_0220a374(&o->sub1, 1);
    o->sub1.v3();
    int a = func_ov002_0220a768(&o->unk_3FB4, 4);
    int b = func_ov002_0220a72c(&o->unk_3FB4, 4);
    func_ov002_0220a0b4(&o->sub1, a, b);
    func_ov002_02208098(o, 0x1d);
}
