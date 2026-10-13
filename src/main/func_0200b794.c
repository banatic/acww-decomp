/* func_0200b794 @ 0x0200b794, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_02077898(const char *);

struct UnkStruct_0200b794 {
    unsigned char unk_00;
    char unk_01;
    char unk_02;
    signed char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
};

void func_0200b794(struct UnkStruct_0200b794 *s, unsigned int *out1, signed char *out2, unsigned short *out3,
                   unsigned char *out4)
{
    out1[0] = s->unk_04;
    out1[1] = s->unk_05;
    *out2 = s->unk_03;
    *out3 = func_02077898(&s->unk_01);
    *out4 = s->unk_00;
}
