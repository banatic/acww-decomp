/* field_actor_10: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220fb30 @ 0x0220fb30, 0x4e bytes, Thumb
 * func_ov003_0220fb14 @ 0x0220fb14, 0x1c bytes, Thumb
 * func_ov003_0220fafc @ 0x0220fafc, 0x16 bytes, Thumb
 * func_ov003_0220fae4 @ 0x0220fae4, 0x18 bytes, Thumb
 */

struct UnkStruct_0220fb14 {
    int unk_00;
    int unk_04;
    unsigned short unk_08;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
};

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov003_0220fb80(void *, int, int, int, unsigned char);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);
extern void func_020779b8(unsigned char *record, int value, int extra);
extern void func_02077978(const unsigned char *record, unsigned int *out, unsigned int *extra);

int func_ov003_0220fb30(int a1, int a2, int a3, int a4, unsigned char a5, int a6, short a7)
{
    char buf1[12];
    char buf2[16];
    int result;

    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x68, a6, a7);
    func_ov003_0220fb80(buf2, a2, a3, a4, a5);
    result = func_0200e894(a1, buf1);
    func_0200e91c(buf1);
    return result;
}

void func_ov003_0220fb14(struct UnkStruct_0220fb14 *out, int a, int b, int c, unsigned char d, unsigned char e)
{
    out->unk_08 = a;
    out->unk_00 = b;
    out->unk_04 = c;
    out->unk_0B = d;
    out->unk_0C = e;
    out->unk_0A = 0;
}

void func_ov003_0220fafc(int r0, int r1, int r2, int r3)
{
    int r5 = r0;
    int r4 = r3;
    func_020779b8((unsigned char *) r0, r1, r2);
    *(unsigned char *) (r5 + 5) = (unsigned char) r4;
}

void func_ov003_0220fae4(unsigned char *r0, int r1, int r2, unsigned char *r3)
{
    unsigned char *r5 = r0;
    unsigned char *r4 = r3;
    unsigned char temp;

    func_02077978(r0, (unsigned int *) r1, (unsigned int *) r2);
    temp = r5[5];
    *r4 = temp;
}
