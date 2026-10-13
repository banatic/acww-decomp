/* func_ov119_0229b7c8 @ 0x0229b7c8, 0x20 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229b7c8 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void vfunc();
};
extern "C" void func_ov002_0220a0ec(UnkStruct_0229b7c8 *);
struct Main {
    char pad_00[0xda8];
    UnkStruct_0229b7c8 sub;
};
extern "C" void func_ov119_0229b7c8(Main *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.vfunc();
}
