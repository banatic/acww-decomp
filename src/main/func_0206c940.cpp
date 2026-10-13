/* func_0206c940 @ 0x0206c940, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206c940 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
};

struct UnkStruct_0206c940_2 {
    char pad_00[0x2c];
    UnkStruct_0206c940 *obj;
};

extern "C" UnkStruct_0206c940 *func_02067f74(UnkStruct_0206c940 *);
extern "C" void func_020a9334(UnkStruct_0206c940_2 *, int);
extern "C" void func_020a7994(void *, int);

extern "C" void func_0206c940(UnkStruct_0206c940_2 *base)
{
    UnkStruct_0206c940 *p = func_02067f74(base->obj);
    int ret = p->f3();
    func_020a9334(base, ret);

    UnkStruct_0206c940 *q = func_02067f74(base->obj);
    int ret2 = q->f3();
    func_020a7994((char *) base->obj + 0x1a58, ret2);

    *((int *) ((char *) base->obj + 0x1a60)) = 1;
}
