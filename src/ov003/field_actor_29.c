/* field_actor_29: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02212c10 @ 0x02212c10, 0x48 bytes, Thumb
 * func_ov003_02212bf4 @ 0x02212bf4, 0x1c bytes, Thumb
 * func_ov003_02212bec @ 0x02212bec, 0x8 bytes, Thumb
 * func_ov003_02212bd8 @ 0x02212bd8, 0x14 bytes, Thumb
 */

struct UnkStruct_02212bf4 {
    int a;
    int b;
    int c;
    short d;
    char e;
    char unk_0F;
};

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov003_02212d04(void *, unsigned char, unsigned char, unsigned char);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);

int func_ov003_02212c10(int a1, unsigned char *p2, unsigned char *p3, unsigned char *p4, int a5, short a6)
{
    int saved_a1 = a1;
    int result;
    char local1[12];
    char local2[20];

    func_0200e92c(local1);
    func_0200e90c(local1, 0x59, a5, a6);
    func_ov003_02212d04(local2, *p2, *p3, *p4);
    result = func_0200e894(saved_a1, local1);
    func_0200e91c(local1);
    return result;
}

void func_ov003_02212bf4(struct UnkStruct_02212bf4 *dst, const struct UnkStruct_02212bf4 *src, short d, char e)
{
    dst->a = src->a;
    dst->b = src->b;
    dst->c = src->c;
    dst->d = d;
    dst->e = e;
    dst->unk_0F = 0;
}

void func_ov003_02212bec(unsigned char *p0, int p1, int p2, int p3)
{
    p0[0] = p1;
    p0[1] = p2;
    p0[2] = p3;
}

void func_ov003_02212bd8(unsigned char *r0, unsigned char *r1, unsigned char *r2, unsigned char *r3)
{
    unsigned char a, b, c;
    a = r0[0];
    r1[0] = a;
    b = r0[1];
    r2[0] = b;
    c = r0[2];
    r3[0] = c;
}
