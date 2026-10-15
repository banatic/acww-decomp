/* func_ov048_022611a0 @ 0x022611a0, 0x50 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc6c(void);
extern void func_0206844c(void *a, char *b, int c);
extern int func_ov048_02262658(void *receiver);
extern void func_ov048_022616b8(void *p, int q);
extern int data_ov048_02263d20;

struct UnkStruct_022611a0 {
    char pad_00[0x40];
    void *unk_40;
};

void func_ov048_022611a0(struct UnkStruct_022611a0 *self)
{
    char buf[8];
    if (func_0206fc6c()) {
        buf[0] = 0x59;
        func_0206844c(self->unk_40, buf, data_ov048_02263d20);
    } else {
        buf[1] = 0x58;
        func_0206844c(self->unk_40, buf + 1, data_ov048_02263d20);
        func_ov048_02262658(self);
    }
    func_ov048_022616b8(self, 0);
}
