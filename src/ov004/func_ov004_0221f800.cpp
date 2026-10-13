/* func_ov004_0221f800 @ 0x0221f800, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221f800 {
    virtual void v0();
    virtual void v1();
    virtual void vcall();
};

extern "C" void func_0202dc3c(UnkStruct_0221f800 *self, void *v, int k);

extern "C" void func_ov004_0221f800(UnkStruct_0221f800 *self, void *v)
{
    self->vcall();
    func_0202dc3c(self, v, 0x11);
    *(void **) ((char *) self + 0x1a4) = v;
}
