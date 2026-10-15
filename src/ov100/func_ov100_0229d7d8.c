/* func_ov100_0229d7d8 @ 0x0229d7d8, 0x4c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d7d8 {
    char pad_00[0x218c];
    char unk_218C;
    char pad_218D[0x790];
    unsigned char unk_291D;
    char pad_291E[2];
    unsigned char unk_2920;
};

extern int func_ov002_02207d24(void *ptr, int arg);
extern void func_ov100_0229cd7c(struct UnkStruct_0229d7d8 *self, int arg);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov100_0229ce58(struct UnkStruct_0229d7d8 *self);
extern void func_ov094_022999c0(void);

void func_ov100_0229d7d8(struct UnkStruct_0229d7d8 *self, int arg)
{
    self->unk_2920 = arg;
    func_ov002_02207d24(&self->unk_218C, 1);
    func_ov100_0229cd7c(self, arg);
    if (self->unk_291D == 1) {
        func_ov002_02208098((void *) (self), 3);
    }
    ((void) (func_ov100_0229ce58(self)), func_ov094_022999c0());
}
