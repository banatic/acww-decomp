/* func_020898e8 @ 0x020898e8, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned short unk_04;
} UnkStruct_020898e8;

extern void MIi_CpuCopy32(void *dst, const void *src, unsigned int size);
extern void MIi_CpuCopyFast(void *dst, const void *src, unsigned int size);
extern UnkStruct_020898e8 data_021d2920;
extern char data_021d2928[];
extern char data_021d2940[];
extern char data_021d2d20[];
extern unsigned int data_021d2910;
extern unsigned int data_021d2914;
extern unsigned int data_021d2918;
extern unsigned int data_021d291c;

void func_020898e8(void)
{
    UnkStruct_020898e8 *s;
    unsigned int zero;

    s = &data_021d2920;
    zero = 0;

    s->unk_00 = 0xC0;
    s->unk_04 = 0;

    MIi_CpuCopy32(s, data_021d2928, 0x18);
    MIi_CpuCopyFast(s, data_021d2940, 0x3e0);
    MIi_CpuCopyFast(s, data_021d2d20, 0x400);

    data_021d2914 = zero;
    data_021d2910 = zero;
    data_021d291c = zero;
    data_021d2918 = zero;
}
