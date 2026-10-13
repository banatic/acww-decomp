/* func_ov146_0229a578 @ 0x0229a578, 0x24 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *, int);

struct UnkStruct_0229a578 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229a578_2 {
    unsigned char pad_00[0x15cc];
    UnkStruct_0229a578 obj;
};

extern "C" void func_ov146_0229a578(UnkStruct_0229a578_2 *self)
{
    func_ov002_0220a374(&self->obj, 0);
    self->obj.v3();
}
