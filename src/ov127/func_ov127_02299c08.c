/* func_ov127_02299c08 @ 0x02299c08, 0xd0 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov127_02299cd8(void *self, int param1, int param2, int param3);
extern int func_ov127_02299878(void *self, int a);
extern void func_ov127_02299868(void *self, int a);
extern void func_ov127_02299858(void *self, int a);
extern void func_02004658(int a);
extern void func_02004644(int a, int b);
extern void func_020041bc(int a);
extern unsigned char data_ov127_0229b5e0[];

struct UnkStruct_02299c08 {
    char pad_00[0x2824];
    short unk_2824;
    short unk_2826;
    short unk_2828;
    char pad_282A[0x2834 - 0x282A];
    unsigned char unk_2834;
};

void func_ov127_02299c08(struct UnkStruct_02299c08 *self, int param1, int param2)
{
    int old1 = self->unk_2828;
    int old2 = self->unk_2824;
    int old3 = self->unk_2826;
    int changed;

    func_ov127_02299cd8(self, param1, 4, param2);
    self->unk_2834 = (unsigned char) param1;

    changed = 0;
    if (old1 != self->unk_2828 || old2 != self->unk_2824 || old3 != self->unk_2826) {
        changed = 1;
    }

    if (old3 != self->unk_2826) {
        if (self->unk_2826 == -0x18 || self->unk_2826 == 0x54) {
            changed = 0;
        }
    }

    if (changed != 0) {
        if (func_ov127_02299878(self, 8) == 0) {
            func_ov127_02299868(self, 8);
            func_02004658(0x883);
        }
    } else {
        if (func_ov127_02299878(self, 8) == 1) {
            func_ov127_02299858(self, 8);
            func_02004644(0x883, 1);
        }
    }

    if (func_ov127_02299878(self, 8) != 0 && param2 != 0) {
        func_020041bc(data_ov127_0229b5e0[param1]);
    }
}
