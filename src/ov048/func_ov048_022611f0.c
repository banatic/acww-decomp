/* func_ov048_022611f0 @ 0x022611f0, 0x6c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022611f0;
extern int func_0206fc6c(struct UnkStruct_022611f0 *self);
extern int func_0206fc8c(void);
extern void func_02073100(int x);
extern int func_020eb868(int x);
extern void func_0206844c(void *ctx, char *msg, int val);
extern void func_ov048_022616b8(struct UnkStruct_022611f0 *self, int param);
extern int data_ov048_02263d20;

struct UnkStruct_022611f0 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x3ec - 0x44];
    int unk_3EC;
};

void func_ov048_022611f0(struct UnkStruct_022611f0 *self)
{
    char msg[2];

    if (func_0206fc6c(self)) {
        int x = func_0206fc8c();
        func_02073100(x);
        self->unk_3EC = func_020eb868(x);
        msg[0] = 'b';
        func_0206844c(self->unk_40, &msg[0], data_ov048_02263d20);
        func_ov048_022616b8(self, 0);
    } else {
        func_ov048_022616b8(self, 20);
        msg[1] = 'a';
        func_0206844c(self->unk_40, &msg[1], data_ov048_02263d20);
    }
}
