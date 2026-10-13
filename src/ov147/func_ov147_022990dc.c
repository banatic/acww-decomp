/* func_ov147_022990dc @ 0x022990dc, 0x3c bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xA4];
    int unk_A4;
    short unk_A8;
    unsigned char unk_AA;
} UnkStruct_022990dc;

extern void MI_CpuFill8(void *addr, int a, int b);
extern void func_02002708(int arg);

extern unsigned char data_ov147_0229f2ac[];

void func_ov147_022990dc(UnkStruct_022990dc *self)
{
    self->unk_AA = 1;
    self->unk_A4 = 0;
    self->unk_A8 = 0x4B0;
    MI_CpuFill8((void *) data_ov147_0229f2ac, 0, 0x3800);
    func_02002708(5);
}
