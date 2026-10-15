/* func_0200ee40 @ 0x0200ee40, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct LocalType {
    unsigned int data[12];
};

struct UnkStruct_0200ee40 {
    char pad_00[0x5c];
    char unk_5C;
    char pad_5D[0xc4 - 0x5c - 1];
    char unk_C4;
    char pad_C5[0xd0 - 0xc4 - 1];
    unsigned short unk_D0;
    char pad_D2[0x234 - 0xd0 - 2];
    char unk_234;
    char pad_235[0x298 - 0x234 - 1];
    struct LocalType unk_298;
    char _pad5[0x698 - 0x298 - sizeof(struct LocalType)];
    char unk_698;
};

extern struct LocalType data_021cfe68;
extern int func_0203f8d0(void *a, void *b);
extern void func_020031d4(void *a, void *b);
extern void func_02055d38(void *a, int b);
extern void func_02054848(void *a, int b);
extern int func_02055d0c(void *a, void *b, int c);

void func_0200ee40(struct UnkStruct_0200ee40 *self)
{
    struct LocalType local;
    self->unk_D0 = (unsigned short) func_0203f8d0(&self->unk_C4, &self->unk_5C);
    func_020031d4(self, &local);
    self->unk_298 = local;
    data_021cfe68 = self->unk_298;
    func_02055d38(&self->unk_234, 0);
    func_02054848(&self->unk_234, 0);
    func_02055d0c(&self->unk_234, &self->unk_698, 0xb);
}
