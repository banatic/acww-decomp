/* func_ov100_0229d788 @ 0x0229d788, 0x50 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x218c];
    char unk_218C;
    char pad_218D[0x291d - 0x218c - 1];
    unsigned char unk_291D;
    char pad_291E[0x2920 - 0x291d - 1];
    unsigned char unk_2920;
    char pad_2921[0x2924 - 0x2920 - 1];
    unsigned char unk_2924;
} UnkStruct_0229d788;

extern void func_ov002_02207d24(void *p, int n);
extern void func_ov100_0229cd7c(UnkStruct_0229d788 *self, int v);
extern void func_ov100_0229ce24(UnkStruct_0229d788 *self);
extern void func_ov094_022999c0(void);

void func_ov100_0229d788(UnkStruct_0229d788 *self, int v)
{
    self->unk_2920 = v;
    func_ov002_02207d24(&self->unk_218C, 1);
    func_ov100_0229cd7c(self, v);
    if (self->unk_291D == 1) {
        self->unk_2924 = 5;
    }
    func_ov100_0229ce24(self);
    func_ov094_022999c0();
}
