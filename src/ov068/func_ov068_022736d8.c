/* func_ov068_022736d8 @ 0x022736d8, 0x8c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022736d8 {
    unsigned char pad_00[0xec];
    unsigned char sub[0x148 - 0xec];
    int unk_148;
    unsigned char pad_14C[0x59c - 0x14c];
    unsigned short unk_59C;
    unsigned short unk_59E;
    unsigned short unk_5A0;
} UnkStruct_022736d8;

extern UnkStruct_022736d8 *data_ov068_022787fc;
extern void func_ov068_02273338(UnkStruct_022736d8 *self);
extern void func_02055dc8(void *p, void (*fn)(void *), UnkStruct_022736d8 *self);
extern void func_ov068_022738d8(void *state);
extern unsigned short func_02057a50(void *object, const char *name);
extern char data_ov068_02277988[];
extern char data_ov068_02277990[];
extern char data_ov068_02277998[];
extern int func_ov068_02273230(UnkStruct_022736d8 *self, int a);
extern void func_02004658(int id);

int func_ov068_022736d8(UnkStruct_022736d8 *self)
{
    data_ov068_022787fc = self;
    func_ov068_02273338(self);
    func_02055dc8(self->sub, func_ov068_022738d8, self);
    self->unk_59C = func_02057a50((void *) (self->unk_148), (const char *) (data_ov068_02277988));
    self->unk_59E = func_02057a50((void *) (self->unk_148), (const char *) (data_ov068_02277990));
    self->unk_5A0 = func_02057a50((void *) (self->unk_148), (const char *) (data_ov068_02277998));
    func_ov068_02273230(self, 0);
    func_02004658(0x884);
    func_02004658(0x885);
    return 1;
}
