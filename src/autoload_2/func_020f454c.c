/* func_020f454c @ 0x020f454c, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vtbl Vtbl;
extern const Vtbl data_0213efb4;

typedef struct UnkStruct_020f454c {
    const Vtbl *vtable;
} UnkStruct_020f454c;

typedef struct Global {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
} Global;

extern Global data_021fd1bc;
extern void NNS_SndHeapLoadState(int, int);
extern void func_020edb3c(UnkStruct_020f454c *self);

UnkStruct_020f454c *func_020f454c(UnkStruct_020f454c *self)
{
    int tmp;

    self->vtable = &data_0213efb4;
    tmp = data_021fd1bc.unk_28;
    data_021fd1bc.unk_2C = 0;
    NNS_SndHeapLoadState(tmp, 0);
    func_020edb3c(self);

    return self;
}
