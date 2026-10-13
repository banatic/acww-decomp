/* func_020abbf8 @ 0x020abbf8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020abbf8;

extern "C" void func_020abc6c(UnkStruct_020abbf8 *, int);
extern "C" void func_020aca48(void *);
extern "C" void func_0208f0c4(void *, int);

class Sub20 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4(int a, int b);
};

struct Sub6c {
    char pad_00;
};
struct SubE4 {
    char pad_00;
};

struct UnkStruct_020abbf8 {
    char pad_00[0x18];
    short unk_18;
    short unk_1A;
    char pad_1C[4];
    Sub20 sub20;
    char pad_24[0x48];
    Sub6c unk_6C;
    char pad_6D[0x77];
    SubE4 unk_E4;
    char pad_E5[0x57];
    int unk_13C;
};

extern "C" void func_020abbf8(UnkStruct_020abbf8 *obj)
{
    obj->unk_13C = 1;
    obj->sub20.f4(-obj->unk_18, -obj->unk_1A);
    func_020abc6c(obj, 1);
    func_020aca48(&obj->unk_E4);
    obj = (UnkStruct_020abbf8 *) ((char *) obj + 0x6c);
    func_0208f0c4(obj, 1);
}
