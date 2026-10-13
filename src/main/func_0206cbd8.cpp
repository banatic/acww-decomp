/* func_0206cbd8 @ 0x0206cbd8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206cbd8 {
  public:
    virtual void *f0();
    virtual void *f1();
    virtual void *f2();
    virtual void *f3();
};

struct UnkStruct_0206cbd8_2 {
    char pad_00[0x14a8];
    void *obj14a8;
    char pad_14AC[0x1a58 - (0x14a8 + 4)];
    void *unk_1A58;
    char pad_1A5C[4];
    int unk_1A60;
};

struct UnkStruct_0206cbd8_3 {
    char pad_00[0x2c];
    UnkStruct_0206cbd8_2 *t;
};

extern "C" UnkStruct_0206cbd8 *func_020668d4(void *arg);
extern "C" void func_020a9334(struct UnkStruct_0206cbd8_3 *p, void *ret);
extern "C" void func_020a7994(void *arg1, void *ret);

extern "C" void func_0206cbd8(struct UnkStruct_0206cbd8_3 *p)
{
    void *obj1 = p->t->obj14a8;
    UnkStruct_0206cbd8 *v1 = func_020668d4(obj1);
    void *ret1 = v1->f3();
    func_020a9334(p, ret1);
    UnkStruct_0206cbd8 *v2 = func_020668d4(obj1);
    void *ret2 = v2->f3();
    func_020a7994(&p->t->unk_1A58, ret2);
    p->t->unk_1A60 = 0;
}
