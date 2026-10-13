/* func_020ac1e8 @ 0x020ac1e8, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_0208e508(void *p, int x);

class UnkStruct_020ac1e8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void vfunc4(int a, int b);
};

extern "C" void func_020ac1e8(void *self)
{
    *(int *) ((char *) self + 0x6c) = 0;
    ((UnkStruct_020ac1e8 *) ((char *) self + 0x20))
        ->vfunc4(-*(short *) ((char *) self + 0x18), -*(short *) ((char *) self + 0x1a));
    func_0208e508((UnkStruct_020ac1e8 *) ((char *) self + 0x20), 7);
}
