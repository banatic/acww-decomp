/* func_ov123_0229b6e8 @ 0x0229b6e8, 0x6c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229b6e8 {
    char pad_00[0x1cc];
    unsigned char unk_1CC;
    char pad_1CD[0x4e63];
    unsigned char unk_5030;
};

extern int func_ov002_0220a700(void *p);
extern int func_0208e4bc(void *p);
extern int func_ov002_0220a6e0(void *p);
extern int func_ov002_0220a768(void *p, int x);
extern int func_ov002_0220a72c(void *p, int x);
extern void func_ov002_0220a0b4(void *p, int x, int y);
extern void func_ov123_02299d00(void *p);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);

void func_ov123_0229b6e8(struct UnkStruct_0229b6e8 *self)
{
    if (func_ov002_0220a700(&self->unk_5030)) {
        if (func_0208e4bc(&self->unk_1CC)) {
            int v1 = func_ov002_0220a6e0(&self->unk_5030);
            int v2 = func_ov002_0220a768(&self->unk_5030, -1);
            int v3 = func_ov002_0220a72c(&self->unk_5030, -1);
            func_ov002_0220a0b4(&self->unk_1CC, v1 + v2, v1 + v3);
        }
    } else {
        func_ov123_02299d00(self);
        func_ov002_022080a0(self, 1);
    }
}
