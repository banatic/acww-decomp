/* func_0206c6fc @ 0x0206c6fc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020677d0(void *p);
extern "C" void func_020a9334(void *self, int val);
extern "C" void func_020a7994(void *obj, int val);

class UnkStruct_0206c6fc {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int method();
};

typedef struct UnkStruct_0206c6fc_2 {
    unsigned char pad_00[0x2c];
    void *unk_2C;
} UnkStruct_0206c6fc_2;

extern "C" void func_0206c6fc(UnkStruct_0206c6fc_2 *self)
{
    func_020677d0(self->unk_2C);
    int ret1 = ((UnkStruct_0206c6fc *) ((char *) self->unk_2C + 0x1da8))->method();
    func_020a9334(self, ret1);
    int ret2 = ((UnkStruct_0206c6fc *) ((char *) self->unk_2C + 0x1da8))->method();
    func_020a7994((char *) self->unk_2C + 0x1a58, ret2);
    *(int *) ((char *) self->unk_2C + 0x1a60) = 1;
}
