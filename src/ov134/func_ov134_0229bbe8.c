/* func_ov134_0229bbe8 @ 0x0229bbe8, 0xc4 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229bbe8 UnkStruct_0229bbe8;
struct UnkStruct_0229bbe8 {
    char pad_00[0x18];
    char unk_18[0xa3 - 0x18];
    unsigned char unk_A3;
    unsigned char unk_A4;
    char pad_A5[0xb7 - 0xa4 - 1];
    signed char sbyte_b7;
    char pad_B8[0x804 - 0xb7 - 1];
    char unk_804[0x24];
    char unk_828[0x48];
    char unk_870[1];
    char pad_871[0x2070 - 0x870 - 1];
    char unk_2070[1];
};

extern void func_ov134_022996b4(UnkStruct_0229bbe8 *);
extern void func_ov002_0220a544(void *);
extern int func_ov134_022995c0(UnkStruct_0229bbe8 *, int);
extern int func_020b9bbc(void *, void *, unsigned char, int, int);
extern void func_ov134_022995a0(UnkStruct_0229bbe8 *, int);
extern unsigned short data_021fbe40;

void func_ov134_0229bbe8(UnkStruct_0229bbe8 *self)
{
    func_ov134_022996b4(self);
    func_ov002_0220a544(self->unk_18);
    if (func_ov134_022995c0(self, 2) != 0) {
        if (func_020b9bbc(self->unk_804, self->unk_870, self->unk_A3, 0x800, 0) != 0) {
            func_ov134_022995a0(self, 2);
        }
    }
    if (func_ov134_022995c0(self, 1) != 0) {
        if (func_020b9bbc(self->unk_828, self->unk_2070, self->unk_A4, 0x800, 0) != 0) {
            func_ov134_022995a0(self, 1);
        }
    }
    if (self->sbyte_b7 > 0) {
        if (data_021fbe40 & 0x40) {
            self->sbyte_b7 = 0;
        }
    } else if (self->sbyte_b7 < 0) {
        if (data_021fbe40 & 0x80) {
            self->sbyte_b7 = 0;
        }
    }
}
