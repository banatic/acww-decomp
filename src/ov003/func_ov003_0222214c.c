/* func_ov003_0222214c @ 0x0222214c, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(int *out, int a, int b);
extern int func_020044c0(void *ptr, int a, int b, int c);
extern void func_ov003_02222aa4(void *self);

typedef struct {
    char pad_00[0x18];
    int unk_18;
    int unk_1C;
    int unk_20;
    char pad_24[0x0c];
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    short unk_48;
    char pad_4A[0x16];
} UnkStruct_0222214c;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0222214c_2;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0222214c_3;

void func_ov003_0222214c(UnkStruct_0222214c *self, UnkStruct_0222214c_2 *b, UnkStruct_0222214c_3 *c)
{
    int locals[3];
    int mod1, mod2, mod3;

    func_0204f794(locals, b->unk_00, b->unk_04);

    mod1 = (locals[2] - c->unk_08) / 30;
    mod2 = -(c->unk_04 / 30);
    mod3 = (locals[0] - c->unk_00) / 30;

    self->unk_30 = mod3;
    self->unk_34 = mod2;
    self->unk_38 = mod1;

    self->unk_18 = c->unk_00;
    self->unk_1C = c->unk_04;
    self->unk_20 = c->unk_08;

    self->unk_3C = 0x1000;
    self->unk_40 = 0x1000;
    self->unk_44 = 0x1000;

    if (self->unk_48 != 0) {
        func_ov003_02222aa4(self);
    }

    func_020044c0((char *) self + 0x60, 0x7eb, 0x7f, 0);
}
