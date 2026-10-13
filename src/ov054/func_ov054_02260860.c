/* func_ov054_02260860 @ 0x02260860, 0x34 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206844c(int a, unsigned char *b, int c);

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

extern Elem12 data_ov054_02262fac[];

void func_ov054_02260860(UnkStruct_02260860 *p)
{
    unsigned char flag = 1;
    func_0206844c(p->unk_40, &flag, data_ov054_02262fac[p->unk_B0[0x202]].a);
}
