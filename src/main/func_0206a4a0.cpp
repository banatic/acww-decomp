/* func_0206a4a0 @ 0x0206a4a0, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206a4a0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

extern "C" int func_020a82f8(int k);
extern "C" void func_020a9334(void *self, int v);
extern "C" UnkStruct_0206a4a0 *func_020668d4(UnkStruct_0206a4a0 *o);
extern "C" void func_020a7994(void *p, int v);

extern "C" void func_0206a4a0(unsigned char *self)
{
    UnkStruct_0206a4a0 *obj;

    func_020a9334(self, func_020a82f8(*(int *) (self + 0x5c)));
    obj = *(UnkStruct_0206a4a0 **) (*(char **) (self + 0x24) + 0x14a8);
    func_020a9334(self, func_020668d4(obj)->v3());
    func_020a9334(self, func_020a82f8(6));
    func_020a7994((void *) (*(char **) (self + 0x24) + 0x1a58), func_020668d4(obj)->v3());
    *(int *) (*(char **) (self + 0x24) + 0x1a60) = 0;
}
