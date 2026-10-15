/* func_0207c3b0 @ 0x0207c3b0, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0207c3b0 {
    char pad_00[0x3f60];
    char unk_3F60[0x3f7c - 0x3f60];
    char unk_3F7C[0x4050 - 0x3f7c];
    char unk_4050[8];
    long long unk_4058;
    char unk_4060[4];
} UnkStruct_0207c3b0;

extern void func_0207bee0(UnkStruct_0207c3b0 *self);
extern void func_0208164c(void *b, int d);
extern void func_0207dbe8(void *b, void *f);
extern void func_020800ec(void *b);
extern void func_0207ef3c(void *b, int e);
extern void func_0207d634(void *b);
extern void func_0207a2a4(char *p, int c);
extern void func_02079c30(char *p, int c);
extern int func_0208150c(void *b);
extern int func_02003648(int x);
extern void func_0207ca74(char *p, int v);
extern void MI_CpuCopy8(void *d, void *s, int n);
extern unsigned char *func_0207c498(UnkStruct_0207c3b0 *self, int c);

void func_0207c3b0(UnkStruct_0207c3b0 *self, void *b, int c, int d, unsigned char e, void *f)
{
    func_0207bee0(self);
    func_0208164c(b, d);
    func_0207dbe8(b, f);
    func_020800ec(b);
    func_0207ef3c(b, e);
    func_0207d634(b);
    func_0207a2a4(self->unk_3F7C, c);
    func_02079c30(self->unk_3F60, c);
    func_0207ca74(self->unk_4060, func_02003648(func_0208150c(b)));
    MI_CpuCopy8(f, self->unk_4050, 8);
    if (self->unk_4058 != 0) {
        MI_CpuCopy8(f, &self->unk_4058, 8);
    }
    func_0207c498(self, (signed char) c);
}
