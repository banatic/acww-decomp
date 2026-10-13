/* func_0206c9d0 @ 0x0206c9d0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class VirtualObj {
  public:
    virtual void a();
    virtual void b();
    virtual void c();
    virtual int getValue();
};
struct UnkStruct_0206c9d0;
struct UnkStruct_0206c9d0_2 {
    char pad_00[0x2c];
    UnkStruct_0206c9d0 *unk_2C;
};
extern "C" VirtualObj *func_02067fd4(UnkStruct_0206c9d0 *);
extern "C" void func_020a9334(UnkStruct_0206c9d0_2 *, int);
extern "C" void func_020a7994(char *, int);
extern "C" void func_0206c9d0(UnkStruct_0206c9d0_2 *self)
{
    func_020a9334(self, func_02067fd4(self->unk_2C)->getValue());
    func_020a7994((char *) self->unk_2C + 0x1a58, func_02067fd4(self->unk_2C)->getValue());
    *(int *) ((char *) self->unk_2C + 0x1a60) = 1;
}
