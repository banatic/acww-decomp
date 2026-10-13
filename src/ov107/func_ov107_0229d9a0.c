/* func_ov107_0229d9a0 @ 0x0229d9a0, 0x48 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d9a0 {
    char pad_00[182];
    unsigned char unk_B6;
    char pad_B7[8];
    unsigned char unk_BF;
    char pad_C0[8460];
    char unk_21CC;
};

extern int AOSS_FD_SET(void *p);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov107_0229c990(void *p, int byte, int flag);

void func_ov107_0229d9a0(struct UnkStruct_0229d9a0 *self)
{
    if (AOSS_FD_SET(&self->unk_21CC)) {
        if (self->unk_BF) {
            self->unk_BF--;
        } else {
            func_ov107_0229c990(self, self->unk_B6, 1);
            func_ov002_02208098(self, 2);
        }
    }
}
