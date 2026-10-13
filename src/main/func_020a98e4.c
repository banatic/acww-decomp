/* func_020a98e4 @ 0x020a98e4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[2];
    unsigned char unk_90[0xc];
    unsigned int unk_9C;
    unsigned int unk_A0;
} UnkStruct_020a98e4;

extern void MI_CpuFill8(void *dst, int val, unsigned int n);
extern unsigned char data_021f446c[0x20];
extern unsigned char data_021f4458[0x14];
extern unsigned char data_021f4428[0xc];

void func_020a98e4(UnkStruct_020a98e4 *self)
{
    volatile unsigned char scratch[8];

    (void) &scratch;
    self->unk_8D = 0;
    MI_CpuFill8(self->unk_90, 0, 0xc);
    self->unk_9C = 0;
    self->unk_A0 = 0;
    MI_CpuFill8(data_021f446c, 0, 0x20);
    MI_CpuFill8(data_021f4458, 0, 0x14);
    MI_CpuFill8(data_021f4428, 0, 0xc);
}
