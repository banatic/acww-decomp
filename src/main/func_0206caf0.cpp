/* func_0206caf0 @ 0x0206caf0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
struct UnkStruct_0206caf0;
struct UnkStruct_0206caf0_2;
struct UnkStruct_0206caf0_2 *func_0206807c(void *obj);
void func_020a9334(struct UnkStruct_0206caf0 *self, int a);
void func_020a7994(void *ptr, int b);
}

struct UnkStruct_0206caf0_2 {
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual int f3() = 0;
};

struct UnkStruct_0206caf0 {
    char pad_00[0x2c];
    void *obj;
};

extern "C" void func_0206caf0(struct UnkStruct_0206caf0 *self)
{
    func_020a9334(self, func_0206807c(self->obj)->f3());
    func_020a7994((char *) self->obj + 0x1a58, func_0206807c(self->obj)->f3());
    *(int *) ((char *) self->obj + 0x1a60) = 1;
}
