/* func_02057538 @ 0x02057538, 0xaa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056ffc(void *);
extern void func_020574c4(void *, int *, int *);
extern int func_0205772c(void *);
extern int func_02057778(void *, int, int, int, int, int, int);

typedef struct UnkStruct_02057538 {
    unsigned char pad_00[0x18];
    unsigned char unk_18;
    unsigned char pad_19[0x37];
    int unk_50;
    unsigned char unk_54;
    unsigned char pad_55[0x10];
    unsigned char unk_65;
    unsigned char pad_66[0x12];
    int unk_78;
    unsigned char pad_7C[0x04];
    int unk_80;
    int unk_84;
    int unk_88;
    unsigned char unk_8C;
} UnkStruct_02057538;

int func_02057538(UnkStruct_02057538 *self)
{
    int local0, local1;

    self->unk_88 = self->unk_84;
    func_02056ffc(self);
    func_020574c4(self, &local0, &local1);

    if (self->unk_84 == local0 || self->unk_8C != 0) {
        local0 = -1;
    }
    if (self->unk_80 == local1) {
        local1 = -1;
    }

    {
        int r4 = func_0205772c(&self->unk_54);
        int r3 = func_0205772c(&self->unk_65);
        if (func_02057778(&self->unk_18, self->unk_50, r4, r3, self->unk_78, local0, local1) != 0) {
            if (local0 != -1) {
                self->unk_84 = local0;
            }
            if (local1 != -1) {
                self->unk_80 = local1;
            }
            return 1;
        }
    }
    return 0;
}
