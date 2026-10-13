/* func_ov142_0229b99c @ 0x0229b99c, 0x5c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229b99c_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3(); // vtable offset 0xc
};

struct UnkStruct_0229b99c {
    char pad_00[0x14c];
    UnkStruct_0229b99c_2 obj; // offset 0x14c
    char pad1[0x948 - 0x14c - sizeof(UnkStruct_0229b99c_2)];
    char arr[4][0x24]; // offset 0x948
};

extern "C" void func_020b9ccc(void *);
extern "C" void func_ov142_0229ae60(UnkStruct_0229b99c *);
extern "C" void func_ov002_0220af74(void *);

extern "C" void func_ov142_0229b99c(UnkStruct_0229b99c *self)
{
    func_020b9ccc(&self->arr[0]);
    func_020b9ccc(&self->arr[1]);
    func_020b9ccc(&self->arr[2]);
    func_020b9ccc(&self->arr[3]);
    func_ov142_0229ae60(self);
    func_ov002_0220af74((char *) self + 0x194);
    self->obj.f3();
}
