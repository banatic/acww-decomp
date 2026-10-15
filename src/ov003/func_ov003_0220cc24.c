/* func_ov003_0220cc24 @ 0x0220cc24, 0xe4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200f290(void *self, int param);
extern int func_0200ea0c(void *self, int param);
extern void func_0204f818(int *a, int *b, void *c);
extern unsigned int func_0200fbe0(void *self);
extern int func_020438dc(int arg0, int *arg1, int arg2);
extern int func_0200ffec(void *self);
extern void func_0200e854(void *self);
extern unsigned int *func_0200f27c(void *self, int param);

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char unk_5C[4];
    unsigned char pad_60[0x7f0 - 0x60];
    int unk_7F0;
    unsigned char pad_7F4[0x800 - 0x7f4];
    int unk_800;
    unsigned char pad_804[0x80c - 0x804];
    int unk_80C;
    unsigned char pad_810[0x8e0 - 0x810];
    int unk_8E0;
    int unk_8E4;
} UnkStruct_0220cc24;

void func_ov003_0220cc24(UnkStruct_0220cc24 *self)
{
    int a, b;
    int pair[2];
    unsigned int idx;
    int mode;

    if (func_0200f290(self, 11) != 0) {
        return;
    }
    if (func_0200f290(self, 22) != 0) {
        return;
    }
    if (func_0200ea0c(self, self->unk_7F0) == 0) {
        return;
    }
    if (self->unk_80C != -1) {
        return;
    }

    a = 0;
    b = 0;
    func_0204f818(&a, &b, self->unk_5C);

    idx = func_0200fbe0(self);
    mode = 0;
    switch (idx) {
        case 1:
            mode = 2;
            break;
        case 2:
            mode = 1;
            break;
        case 4:
            mode = 3;
            break;
        case 5:
            mode = 4;
            break;
    }

    pair[0] = a;
    pair[1] = b;
    self->unk_80C = func_020438dc(self->unk_800, pair, mode);
    if (self->unk_80C == -1) {
        return;
    }

    if (func_0200ffec(self) != 0x19) {
        return;
    }
    func_0200e854(self);
    func_0200f27c(self, 0x16);
    func_0200f27c(self, 0x13);

    self->unk_8E0 = a;
    self->unk_8E4 = b;
}
