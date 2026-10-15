/* func_0206c65c @ 0x0206c65c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// Declarations for external functions and types
class UnkStruct_0206c65c;

struct UnkStruct_0206c65c_2 {
    char pad_00[0x2c];
    char *unk_2C;
};

extern "C" int func_02067728(char *p);
extern "C" void func_020a9334(UnkStruct_0206c65c_2 *self, int val);
extern "C" void func_020a7994(char *p, int val);

class UnkStruct_0206c65c {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int method();
};

extern "C" void func_0206c65c(UnkStruct_0206c65c_2 *self)
{
    func_02067728(self->unk_2C);
    int res1 = ((UnkStruct_0206c65c *) (self->unk_2C + 0x1e24))->method();
    func_020a9334(self, res1);
    int res2 = ((UnkStruct_0206c65c *) (self->unk_2C + 0x1e24))->method();
    func_020a7994(self->unk_2C + 0x1a58, res2);
    *((int *) (self->unk_2C + 0x1a60)) = 1;
}
