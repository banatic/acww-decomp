/* func_02058cdc @ 0x02058cdc, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205967c(void *a, void *b);
extern void func_02059674(void *a, int b);
extern void func_020eaca0(void *a, void *b, void *c);

typedef struct UnkStruct_02058cdc {
    unsigned char pad_00[12];
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_02058cdc;

typedef struct UnkStruct_02058cdc_2 {
    unsigned char pad_00[0x60];
    int unk_60;
    unsigned char pad_64[0x20];
    int unk_84;
    int unk_88;
    int unk_8C;
    unsigned char pad_90[0x46];
    short unk_D6;
} UnkStruct_02058cdc_2;

void func_02058cdc(UnkStruct_02058cdc_2 *self)
{
    UnkStruct_02058cdc local;
    func_0205967c(self, &local);
    func_020eaca0(&local.unk_0C, &self->unk_60, &local);
    self->unk_84 = local.unk_0C;
    self->unk_88 = local.unk_10;
    self->unk_8C = local.unk_14;
    func_02059674(self, 1);
    self->unk_D6 = 0;
}
