/* func_ov143_02299f84 @ 0x02299f84, 0x1a bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *p);

struct UnkStruct_02299f84 {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov143_02299f84(void *self)
{
    func_ov002_0220a0ec((void *) ((char *) self + 0xac));
    ((UnkStruct_02299f84 *) ((char *) self + 0xac))->f3();
}
