/* field_actor_anim_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02010c34 @ 0x02010c34, 0x70 bytes, Thumb
 * func_02010bf0 @ 0x02010bf0, 0x44 bytes, Thumb
 * func_02010bac @ 0x02010bac, 0x44 bytes, Thumb
 * func_02010b50 @ 0x02010b50, 0x5c bytes, Thumb
 * func_02010af4 @ 0x02010af4, 0x5c bytes, Thumb
 */

struct S02010BAC;

struct S02010BAC {
    char pad_00[0x770];
    int unk_770;
};

extern int func_0205dc80(char *);
extern int func_0205db38(char *);
extern int func_0205685c(char *, int, int, int, int);
extern int func_0205cf28(int);
extern int func_0205cf1c(int);
extern void func_0205d7b8(unsigned char *, unsigned int, int, int);
extern unsigned int func_0205d8a0(unsigned char *);
extern void func_0205678c(unsigned char *, unsigned int, int, int, unsigned int, unsigned int);
extern void func_02056778(unsigned char *);
extern int func_0205d894(void *p);

void func_02010b50(unsigned char *base, unsigned int *src, unsigned char *src_byte);
void func_02010af4(void *self, int *src, unsigned char *byte);

void func_02010c34(char *base)
{
    int v0;
    int v1;

    v0 = *((int *) (base + 0x3e8));
    v1 = func_0205dc80(base + 0x70d);
    func_0205685c(base + 0x710, v0, v1, 1, func_0205db38(base + 0x70f));

    v0 = *((int *) (base + 0x3e8));
    v1 = func_0205dc80(base + 0x70d);
    func_0205685c(base + 0x73c, v0, v1, 1, func_0205db38(base + 0x70f));
}

void func_02010bf0(int r0, int *r1, int r2)
{
    int r4;
    int r5 = r0;
    int r6 = r2;
    int sp0;
    int r0_val;

    r4 = *(int *) (r5 + 0x76c);
    r0_val = func_0205cf28(*r1);
    sp0 = r0_val;
    if (r0_val == 0x16f && r4 != 0) {
        sp0 = 0;
    }
    if (sp0 != 0x16f) {
        func_02010b50((unsigned char *) r5, (unsigned int *) (&sp0), (unsigned char *) r6);
    }
}

void func_02010bac(struct S02010BAC *s, int *q, int a)
{
    int f, v;
    f = s->unk_770;
    v = func_0205cf1c(*q);
    if (v == 0x16f && f != 0xba) {
        v = 0xba;
    }
    if (v != 0x16f) {
        func_02010af4((void *) s, &v, (unsigned char *) a);
    }
}

void func_02010b50(unsigned char *base, unsigned int *src, unsigned char *src_byte)
{
    unsigned int result;

    func_0205d7b8(base + 0x70e, *src, 1, 0);
    result = func_0205d8a0(base + 0x70e);
    func_0205678c(base + 0x710, result, 0, 0, *src_byte, 0x1000);
    func_02056778(base + 0x710);
    *(unsigned int *) (base + 0x76c) = *src;
}

void func_02010af4(void *self, int *src, unsigned char *byte)
{
    func_0205d7b8((unsigned char *) ((char *) self + 0x70e), *src, 1, 0);
    func_0205678c((unsigned char *) ((char *) self + 0x73c), func_0205d894((char *) self + 0x70e), 0, 0, *byte, 0x1000);
    func_02056778((unsigned char *) ((char *) self + 0x73c));
    *(int *) ((char *) self + 0x770) = *src;
}
