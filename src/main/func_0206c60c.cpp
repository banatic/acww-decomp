/* func_0206c60c @ 0x0206c60c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_0206781c(void *p);
extern "C" void func_020a9334(void *this_, int val);
extern "C" void func_020a7994(int *p, int val);

class UnkStruct_0206c60c {
  public:
    virtual int vf0();
    virtual int vf1();
    virtual int vf2();
    virtual int vf3();
};

struct UnkStruct_0206c60c_2 {
    char pad_00[0x1a58];
    int unk_1A58;
    char pad_1A5C[0x1a60 - 0x1a58 - 4];
    int unk_1A60;
    char pad_1A64[0x1d4c - 0x1a60 - 4];
    UnkStruct_0206c60c obj;
};

struct UnkStruct_0206c60c_3 {
    char pad_00[0x2c];
    UnkStruct_0206c60c_2 *b;
};

extern "C" void func_0206c60c(UnkStruct_0206c60c_3 *this_)
{
    int r1;
    func_0206781c(this_->b);
    r1 = this_->b->obj.vf3();
    func_020a9334(this_, r1);
    r1 = this_->b->obj.vf3();
    func_020a7994(&this_->b->unk_1A58, r1);
    this_->b->unk_1A60 = 1;
}
