/* func_ov142_0229ab80 @ 0x0229ab80, 0x7c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229a6d8(void *self);
extern void func_ov142_0229a4d4(void *self, int);
extern void func_ov142_02299a54(void *self);
extern void func_ov142_022999ec(void *self);
extern void func_ov142_02299a08(void *self);
extern void func_ov142_02299ab8(void *self);
extern void func_ov142_02299658(void *self, int);

typedef struct {
    char pad_00[0xA0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0x14];
    unsigned char bc;
    unsigned char bd;
} UnkStruct_0229ab80;

void func_ov142_0229ab80(UnkStruct_0229ab80 *self, unsigned char value)
{
    if (self->bc == value) {
        return;
    }
    self->bc = value;
    self->bd = value;
    self->unk_A4 = (func_ov142_0229a6d8(self) - 8) << 4;
    if (self->unk_A4 < 0) {
        self->unk_A4 = 0;
    }
    func_ov142_0229a4d4(self, 0);
    self->unk_A0 = 0;
    func_ov142_02299a54(self);
    if (self->unk_A4 == 0) {
        func_ov142_022999ec(self);
    } else {
        func_ov142_02299a08(self);
    }
    func_ov142_02299ab8(self);
    func_ov142_02299658(self, 8);
}
