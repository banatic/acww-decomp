/* func_ov093_022994ac @ 0x022994ac, 0x68 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov093_02298fbc(void *ptr);
extern void MIi_CpuClear16(unsigned short value, void *dst, int size);

typedef struct {
    unsigned char pad_00[5];
    unsigned char unk_05;
    unsigned char pad_06[2];
    unsigned int unk_08;
    unsigned char pad_0C[4];
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned char unk_18[8];
    unsigned char unk_20[0x800];
    unsigned char unk_820[8];
    unsigned char unk_828[0x800];
    unsigned short unk_1028;
} UnkStruct_022994ac;

void func_ov093_022994ac(UnkStruct_022994ac *self, int arg1)
{
    volatile unsigned short v1;
    volatile unsigned short v2;

    self->unk_10 = arg1;
    self->unk_14 = 0x2000;
    self->unk_08 = 0;
    func_ov093_02298fbc(self->unk_18);
    func_ov093_02298fbc(self->unk_820);
    v1 = self->unk_1028;
    MIi_CpuClear16(v1, self->unk_20, 0x800);
    v2 = self->unk_1028;
    MIi_CpuClear16(v2, self->unk_828, 0x800);
    self->unk_05 = 1;
}
