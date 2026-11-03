/* my_designs_6: 4 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229adc0 @ 0x0229adc0, 0x12 bytes, Thumb
 * func_ov121_0229adac @ 0x0229adac, 0x14 bytes, Thumb
 * func_ov121_0229ad68 @ 0x0229ad68, 0x44 bytes, Thumb
 * func_ov121_0229ad40 @ 0x0229ad40, 0x28 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x9c];
    unsigned int flag;
} UnkStruct_0229adac;

extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;

void func_ov121_0229adc0(void *param0, int param1)
{
    unsigned int *p;
    unsigned int r3;
    unsigned int r2;

    p = (unsigned int *) ((char *) param0 + 0x9c);
    r3 = *p;
    r2 = 1;
    r2 <<= param1;
    r3 |= r2;
    *((unsigned int *) ((char *) param0 + 0x9c)) = r3;
}

int func_ov121_0229adac(UnkStruct_0229adac *self, int bit)
{
    return (self->flag & (1 << bit)) ? 1 : 0;
}

int func_ov121_0229ad68(void)
{
    int diff1;
    int diff2;

    diff1 = data_021f6c60 - data_021f6c58;
    if (diff1 < 0) {
        diff1 = -diff1;
    }
    if (diff1 > 0x10) {
        return 1;
    }

    diff2 = data_021f6c5c - data_021f6c54;
    if (diff2 < 0) {
        diff2 = -diff2;
    }
    if (diff2 > 0x10) {
        return 1;
    }

    return 0;
}

void func_ov121_0229ad40(short *r0)
{
    short *r1;
    short r2;
    unsigned char r3;

    r2 = *(short *) ((char *) r0 + 0xa8);
    r3 = data_021f6c58;
    r2 += r3;
    r1 = (short *) ((char *) r0 + 0xa4);
    *r1 = r2;

    r2 = *(short *) ((char *) r0 + 0xaa);
    r3 = data_021f6c54;
    r2 += r3;
    r0 = (short *) ((char *) r0 + 0xa6);
    *r0 = r2;
}
