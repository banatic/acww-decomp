/* func_ov144_02299df4 @ 0x02299df4, 0x78 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuClear16(int, void *, int);
extern void MIi_CpuCopy16(void *, const void *, int);
extern void func_ov144_02299670(void *, int);

typedef struct {
    char pad_00[0xb6];
    short unk_B6;
    char pad_B8[0x852];
    unsigned char dest[9][128];
    char pad_D8A[0x380];
    unsigned char src[16][128];
} UnkStruct_02299df4;

void func_ov144_02299df4(UnkStruct_02299df4 *self)
{
    int rem = (self->unk_B6 + 9) % 9;
    int sub = self->unk_B6 & 0xF;
    volatile unsigned short v = 0x10;
    int zero = 0;
    int i;

    MIi_CpuClear16(v, (void *) self->src, 0x800);

    i = 0;
    do {
        MIi_CpuCopy16(&self->dest[rem], &self->src[sub], 0x80);
        rem++;
        if (rem >= 9) {
            rem = zero;
        }
        sub = (sub + 1) & 0xF;
        i++;
    } while (i < 9);

    func_ov144_02299670(self, 8);
}
