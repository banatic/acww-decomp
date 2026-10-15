/* func_ov048_02261a38 @ 0x02261a38, 0x50 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02261a38 {
    char pad_00[0x40];
    int unk_40;
};

extern int data_ov048_02263d20;
extern void func_0206844c(int a, char *b, int c);
extern int func_ov004_0222d4f4(void);
extern void func_0207428c(void);
extern int func_020ec1e8(void);
extern void func_ov048_022616b8(struct UnkStruct_02261a38 *self, int arg);
extern int func_ov048_02262658(void *receiver);

void func_ov048_02261a38(struct UnkStruct_02261a38 *self, int flag)
{
    char c[8];

    if (flag != 0) {
        return;
    }

    c[0] = 0x52;

    func_0206844c(self->unk_40, c, data_ov048_02263d20);
    func_ov004_0222d4f4();
    func_0207428c();

    if (func_020ec1e8() == 3 || func_020ec1e8() == 4) {
        func_ov048_022616b8(self, 0x14);
    } else {
        func_ov048_02262658(self);
    }
}
