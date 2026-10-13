/* func_0203723c @ 0x0203723c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8];
    unsigned int unk_08;
    unsigned char pad_0C[0x3];
    unsigned char unk_0F;
    unsigned char unk_10;
} UnkStruct_0203723c;

extern void func_020371f0(UnkStruct_0203723c *self);
extern void func_02037190(UnkStruct_0203723c *self);

int func_0203723c(UnkStruct_0203723c *self)
{
    if (self->unk_0F == 0) {
        func_020371f0(self);
        self->unk_08 = 24;
        func_02037190(self);
    }
    self->unk_10 = 0;
    return 0;
}
