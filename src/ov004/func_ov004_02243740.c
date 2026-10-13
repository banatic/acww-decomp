/* func_ov004_02243740 @ 0x02243740, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02243740 {
    char unk_00[0x168];
    short unk_168;
} UnkStruct_02243740;

extern void func_ov004_022449ec(UnkStruct_02243740 *self, int a, int b, int c);
extern void func_ov004_0224497c(UnkStruct_02243740 *self, int a, int b, int c);
extern int func_020644cc(int a);
extern int FX_Div(int a, int b);

void func_ov004_02243740(UnkStruct_02243740 *self)
{
    func_ov004_022449ec(self, 0x38e, 0x28, 0x50);
    self->unk_168 = (short) (self->unk_168 + (short) FX_Div(0x2000, (func_020644cc(4) + 5) << 12));
    func_ov004_0224497c(self, self->unk_168, 0x1000, (func_020644cc(4) + 0xa) << 12);
}
