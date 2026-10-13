/* func_ov144_0229a894 @ 0x0229a894, 0xb4 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    int unk_A4;
    unsigned char pad_A8[0xb8 - 0xa8];
    short unk_B8;
    short unk_BA;
    short unk_BC;
    unsigned char pad_BE[0xc0 - 0xbe];
    unsigned char unk_C0;
    unsigned char pad_C1[0x86c - 0xc1];
    unsigned short table[1];
} UnkStruct_0229a894;
extern void func_02060984(unsigned short);
extern void func_ov144_02299b48(UnkStruct_0229a894 *self, int);
extern void func_ov144_0229a328(UnkStruct_0229a894 *self);
extern void func_ov144_02299e6c(UnkStruct_0229a894 *self, int);
extern void func_ov144_0229a378(UnkStruct_0229a894 *self);
extern void func_ov144_0229a7c8(UnkStruct_0229a894 *self);
void func_ov144_0229a894(UnkStruct_0229a894 *self)
{
    if (self->unk_C0 != 0) {
        self->unk_C0--;
    } else {
        func_02060984(self->table[self->unk_BA]);
        if (self->unk_BA < self->unk_BC) {
            self->unk_BC -= 1;
        }
        func_ov144_02299b48(self, -1);
        func_ov144_0229a328(self);
        self->unk_A4 = (self->unk_B8 - 8) << 4;
        if (self->unk_A4 < 0) {
            self->unk_A4 = 0;
        }
        if (self->unk_9C > self->unk_A4) {
            self->unk_9C = self->unk_A4;
        }
        func_ov144_02299e6c(self, self->unk_9C);
        self->unk_A0 = self->unk_9C;
        func_ov144_0229a378(self);
        func_ov144_0229a7c8(self);
    }
}
