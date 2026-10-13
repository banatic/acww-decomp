/* func_ov145_02299b1c @ 0x02299b1c, 0x78 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuClear16(int, void *, int);
extern void MIi_CpuCopy16(void *, const void *, int);
extern void func_ov145_02299658(void *, int);

typedef struct {
    char pad_00[0xb6];
    short unk_B6;
    char pad_B8[0xc0e];
    unsigned char dest[9][128];
    char pad_1146[0x380];
    unsigned char src[16][128];
} UnkStruct_02299b1c;

void func_ov145_02299b1c(UnkStruct_02299b1c *self)
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

    func_ov145_02299658(self, 8);
}
