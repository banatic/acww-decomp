/* func_ov003_02223580 @ 0x02223580, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055478(void *, void *);
extern void func_02055140(void *, void *);
extern void func_02055de0(void *, void (*)(void), int, int, void *, int);
extern void func_0200451c(int *);
extern void func_ov003_02222c68(void *);
extern void func_ov003_02222c34(void);
extern void *data_ov003_0223cf78;

typedef struct {
    unsigned char pad_00[0x8];
    int unk_08;
    unsigned char pad_0C[0xD4 - 0x8 - 0x4];
    int unk_D4;
    unsigned char pad_D8[0xE0 - 0xD4 - 0x4];
    int unk_E0;
} UnkStruct_02223580;

void func_ov003_02223580(UnkStruct_02223580 *self)
{
    func_02055478(&self->unk_08, data_ov003_0223cf78);
    func_02055140(&self->unk_08, data_ov003_0223cf78);
    self->unk_D4 = 8;
    func_02055de0(&self->unk_08, func_ov003_02222c34, 2, 2, self, 0);
    func_0200451c(&self->unk_E0);
    func_ov003_02222c68(self);
}
