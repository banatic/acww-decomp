/* func_02067540 @ 0x02067540, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020a82a4(void *p);
extern "C" int func_020a829c(void *p);
extern "C" void func_02067648(void *self, int arg);

class ClassA {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5(int arg);
};

struct UnkStruct_02067540 {
    char pad_00[0x14a8];
    ClassA *obj;
    char unk_14AC[1];
    char pad_14AD[0x9e8];
    unsigned char flag;
};

extern "C" void func_02067540(UnkStruct_02067540 *self)
{
    if (self->flag == 0) {
        return;
    }
    func_02067648(self, func_020a82a4(&self->unk_14AC));
    int res2 = func_020a829c(&self->unk_14AC);
    self->obj->v5(res2);
    self->flag = 0;
}
