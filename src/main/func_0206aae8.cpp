/* func_0206aae8 @ 0x0206aae8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct VtblObj {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
};

struct UnkStruct_0206aae8 {
    int unk_00;
    int unk_04;
    char pad_08[0x1c];
    void *obj;
};

extern "C" int func_020a7cdc(int, int, int);
extern "C" int func_020676d0(void *);
extern "C" void func_020a93e8(UnkStruct_0206aae8 *, int);
extern "C" void func_020a9334(UnkStruct_0206aae8 *, int);

extern "C" void func_0206aae8(UnkStruct_0206aae8 *p)
{
    int r4 = p->unk_04;
    int r6 = func_020a7cdc(r4, 1, 7);
    if (r6 == 0) {
        return;
    }
    if (func_020676d0(p->obj) == 0) {
        return;
    }
    func_020a93e8(p, r6 - r4);
    VtblObj *obj = (VtblObj *) ((char *) p->obj + 0x1e4c);
    func_020a9334(p, obj->f3());
}
