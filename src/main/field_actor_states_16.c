/* field_actor_states_16: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200b7e8 @ 0x0200b7e8, 0x54 bytes, Thumb
 * func_0200b7c0 @ 0x0200b7c0, 0x28 bytes, Thumb
 * func_0200b794 @ 0x0200b794, 0x2c bytes, Thumb
 */

typedef struct {
    int a;
    short b;
} UnkStruct_0200b7e8;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
} UnkStruct_0200b7c0;

struct UnkStruct_0200b794 {
    unsigned char unk_00;
    char unk_01;
    char unk_02;
    signed char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
};

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200b894(void *, int *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020778b0(unsigned char *dst, int param);
extern unsigned short func_02077898(const char *);

int func_0200b7e8(void *p0, int *p1, int p2, int p3, int p4, short p5)
{
    int pair[2];
    char obj[12];
    char tmp[16];
    int result;

    func_0200e92c(obj);
    func_0200e90c(obj, 0x19, p4, p5);
    pair[0] = p1[0];
    pair[1] = p1[1];
    func_0200b894(tmp, pair, -1, p2, p3);
    result = func_0200e894(p0, obj);
    func_0200e91c(obj);
    return result;
}

void func_0200b7c0(UnkStruct_0200b7c0 *dst, const unsigned int *src, unsigned char byte1, int param4, unsigned char byte2)
{
    dst->unk_04 = (unsigned char) src[0];
    dst->unk_05 = (unsigned char) src[1];
    dst->unk_03 = byte1;
    func_020778b0(&dst->unk_01, param4);
    dst->unk_00 = byte2;
}

void func_0200b794(struct UnkStruct_0200b794 *s, unsigned int *out1, signed char *out2, unsigned short *out3,
                   unsigned char *out4)
{
    out1[0] = s->unk_04;
    out1[1] = s->unk_05;
    *out2 = s->unk_03;
    *out3 = func_02077898(&s->unk_01);
    *out4 = s->unk_00;
}
