/* func_0206dd8c @ 0x0206dd8c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020df258;
extern void *func_020a8cac(void *self);
extern void func_020a8c1c(void *self);

typedef struct UnkStruct_0206dd8c {
    void *unk_00;
    char pad_04[0x60];
    int unk_64;
    unsigned short unk_68;
    char pad_6A[3];
    char unk_6D;
    char unk_6E;
    char pad_6F;
    char unk_70;
    char unk_71;
} UnkStruct_0206dd8c;

UnkStruct_0206dd8c *func_0206dd8c(UnkStruct_0206dd8c *self)
{
    func_020a8cac(self);
    self->unk_00 = &data_020df258;
    func_020a8c1c(self);
    self->unk_64 = 0;
    self->unk_68 = 0;
    self->unk_6D = 0;
    self->unk_6E = 0;
    self->unk_70 = 0;
    self->unk_71 = 0;
    return self;
}
