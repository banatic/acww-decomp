/* func_020bf9d4 @ 0x020bf9d4, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct UnkStruct_020bf9d4_2 {
    u8 pad_00[0x4];
    s32 unk_04; // 0x04
    u8 pad_08[0x34 - 0x08];
    s32 unk_34; // 0x34
    s32 unk_38; // 0x38
    u8 pad_3C[0x40 - 0x3c];
    s32 unk_40; // 0x40
    s32 unk_44; // 0x44
    u8 pad_48[0x60 - 0x48];
    u32 unk_60; // 0x60
    s32 unk_64; // 0x64
    u8 pad_68[0x6c - 0x68];
    s32 unk_6C; // 0x6c
    s32 unk_70; // 0x70
} UnkStruct_020bf9d4;

extern void func_020be5d0(int a, int b, int c, int d);
extern void func_020eabc8(int *a, int b);
extern void VEC_Add(int *a, int *b, int *c);

extern unsigned char data_021fbb14[];
extern unsigned char data_021fbee8[];

void func_020bf9d4(UnkStruct_020bf9d4 *self)
{
    if (self->unk_64 > 0) {
        self->unk_64--;
        if (self->unk_64 > 0) {
            return;
        }
        if ((self->unk_60 & 3) != 0) {
            return;
        }
        func_020be5d0((unsigned int) data_021fbb14, 7, 0x805, (unsigned int) data_021fbee8);
        return;
    } else {
        int *p34 = &self->unk_34;
        int *p40 = &self->unk_40;
        int r1;
        int r0;
        int r6;
        s32 x38;

        p40[0] = p40[0] + self->unk_6C;
        p40[1] = p40[1] + self->unk_70;

        func_020eabc8(p40, 0xfc3);
        VEC_Add(p34, p40, p34);

        r1 = 1;
        r0 = r1;
        r6 = r1;
        x38 = p34[1];

        if (x38 >= -40960 && x38 <= 0x000ca000) {
            r6 = 0;
        }
        if (r6 == 0 && p34[0] >= -40960) {
            r0 = 0;
        }
        if (r0 == 0 && p34[0] <= 0x0010a000) {
            r1 = 0;
        }
        if (r1 != 0) {
            self->unk_04 = 3;
        }
    }
}
