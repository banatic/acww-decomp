/* func_020a9a90 @ 0x020a9a90, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3d34;
extern unsigned char data_021f43ec;

struct UnkStruct_020a9a90_2 {
    unsigned char data[0x48];
};

extern void FS_InitFile(struct UnkStruct_020a9a90_2 *sub);
extern void *MI_CpuFill8(void *s, int c, unsigned int n);

struct UnkStruct_020a9a90 {
    void *unk_00;
    unsigned char unk_04;
    unsigned char unk_05[0x3F];
    struct UnkStruct_020a9a90_2 unk_44;
    unsigned char unk_8C;
    unsigned char unk_8D;
    unsigned char pad_8E[0x0E];
    unsigned int unk_9C;
    unsigned int unk_A0;
};

struct UnkStruct_020a9a90 *func_020a9a90(struct UnkStruct_020a9a90 *self, unsigned char c)
{
    self->unk_00 = &data_020e3d34;
    self->unk_04 = c;
    self->unk_8C = 0;
    self->unk_8D = data_021f43ec;
    self->unk_9C = 0;
    self->unk_A0 = 0;
    FS_InitFile(&self->unk_44);
    MI_CpuFill8(self->unk_05, 0, sizeof(self->unk_05));
    return self;
}
