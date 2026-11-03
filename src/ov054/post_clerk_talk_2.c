/* post_clerk_talk_2: 3 functions, module ov054
 * mwccarm 1.2/base -O4,s
 * func_ov054_02260894 @ 0x02260894, 0x18 bytes, Thumb
 * func_ov054_02260860 @ 0x02260860, 0x34 bytes, Thumb
 * func_ov054_0226083c @ 0x0226083c, 0x22 bytes, Thumb
 */

typedef struct {
    char unk_00[0x40];
    int unk_40;
    char unk_44[0x6C];
    int *unk_B0;
} UnkStruct_02260860;

typedef struct {
    int a;
    char pad_04[8];
} Elem12;

extern int func_02015828(int, int);
extern void func_ov054_02261cc4(int, int);
extern void func_0206844c(int a, unsigned char *b, int c);
extern Elem12 data_ov054_02262fac[];
extern void func_020157c8(void *p, int a, int b);

void func_ov054_02260894(int r0)
{
    func_02015828(r0, 1);
    func_ov054_02261cc4(r0, 1);
}

void func_ov054_02260860(UnkStruct_02260860 *p)
{
    unsigned char flag = 1;
    func_0206844c(p->unk_40, &flag, data_ov054_02262fac[p->unk_B0[0x202]].a);
}

void func_ov054_0226083c(void *p)
{
    func_020157c8(p, 0x26, 0);
    func_02015828((int) p, 2);
    func_ov054_02261cc4((int) p, 2);
}
