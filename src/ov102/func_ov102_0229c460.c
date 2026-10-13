/* func_ov102_0229c460 @ 0x0229c460, 0x60 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int n);
extern void func_ov002_02208098(void *self, int n);
extern void func_ov102_0229c4c0(void *self, int n);
extern void func_0206fc4c(int n);
extern void func_020984e8(void);
extern void func_0209898c(void);
extern int func_0203a674(void);
extern void MI_CpuCopy8(void *addr, int v, int n);

struct UnkStruct_0229c460 {
    char pad_00[0x25a9];
    unsigned char unk_25A9;
};

void func_ov102_0229c460(struct UnkStruct_0229c460 *self, int flag)
{
    int v;

    RtcSendPxiCommand(0x27);
    if (flag) {
        self->unk_25A9 = 5;
    } else {
        self->unk_25A9 = 0;
    }
    func_ov002_02208098(self, 0xf);
    func_ov102_0229c4c0(self, 1);
    func_0206fc4c(1);
    func_020984e8();
    func_0209898c();
    v = func_0203a674();
    MI_CpuCopy8((char *) self + 0x24e8, v, 0xb4);
}
