/* func_0206a9e0 @ 0x0206a9e0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206a9e0_2 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7(int);
};

extern "C" void func_020a8750(void *);

struct UnkStruct_0206a9e0 {
    char pad_00[0x24];
    void **unk_24;
};

extern "C" void func_0206a9e0(UnkStruct_0206a9e0 *self)
{
    UnkStruct_0206a9e0_2 *obj = (UnkStruct_0206a9e0_2 *) self->unk_24[0x52a];
    func_020a8750((char *) self + 0x38);
    obj->m7(2);
}
