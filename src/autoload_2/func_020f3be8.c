/* func_020f3be8 @ 0x020f3be8, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f45c4(void *self);
extern void *func_020f9888(void *ptr);
extern char data_0213ea04;

typedef struct UnkStruct_020f3be8 {
    void *unk_00;
    unsigned char unk_04;
    unsigned char pad_05[3];
    char unk_08[20];
    unsigned char unk_1C;
} UnkStruct_020f3be8;

UnkStruct_020f3be8 *func_020f3be8(UnkStruct_020f3be8 *self)
{
    func_020f45c4(self);
    self->unk_00 = &data_0213ea04;
    func_020f9888(self->unk_08);
    self->unk_04 = 10;
    self->unk_1C = 0;
    return self;
}
