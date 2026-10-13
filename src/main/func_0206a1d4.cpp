/* func_0206a1d4 @ 0x0206a1d4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206a1d4 UnkStruct_0206a1d4;

typedef struct UnkStruct_0206a1d4_2 {
    char pad_00[0x24];
    UnkStruct_0206a1d4 *unk_24;
} UnkStruct_0206a1d4_2;

class UnkStruct_0206a1d4_3 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int vfunc();
};

extern "C" UnkStruct_0206a1d4_3 *func_02067f74(UnkStruct_0206a1d4 *p);
extern "C" void func_020a9334(UnkStruct_0206a1d4_2 *self, int v);
extern "C" void func_020a7994(char *p, int w);

extern "C" void func_0206a1d4(UnkStruct_0206a1d4_2 *self)
{
    func_020a9334(self, func_02067f74(self->unk_24)->vfunc());
    func_020a7994((char *) self->unk_24 + 0x1a58, func_02067f74(self->unk_24)->vfunc());
    *(int *) ((char *) self->unk_24 + 0x1a60) = 1;
}
