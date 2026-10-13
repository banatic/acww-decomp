/* func_0206a264 @ 0x0206a264, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206a264 {
    unsigned char pad_00[0x1a58];
    int x;
    int pad_1A5C;
    int z;
};

struct UnkStruct_0206a264_2 {
    unsigned char pad_00[0x24];
    UnkStruct_0206a264 *unk_24;
};

class UnkStruct_0206a264_3 {
  public:
    virtual int f1() = 0;
    virtual int f2() = 0;
    virtual int f3() = 0;
    virtual int f4() = 0;
};

extern "C" UnkStruct_0206a264_3 *func_02067fd4(UnkStruct_0206a264 *);
extern "C" void func_020a9334(UnkStruct_0206a264_2 *, int);
extern "C" void func_020a7994(int *, int);

extern "C" void func_0206a264(UnkStruct_0206a264_2 *p)
{
    int r;
    r = func_02067fd4(p->unk_24)->f4();
    func_020a9334(p, r);
    r = func_02067fd4(p->unk_24)->f4();
    func_020a7994(&p->unk_24->x, r);
    p->unk_24->z = 1;
}
