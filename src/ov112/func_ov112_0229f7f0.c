/* func_ov112_0229f7f0 @ 0x0229f7f0, 0x5a bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f7f0;
typedef struct UnkStruct_0229f7f0 {
    char pad_00[0x94];
    int unk_94;
    int unk_98;
    int unk_9C;
} UnkStruct_0229f7f0;

extern int func_ov112_0229f84c(UnkStruct_0229f7f0 *self, int a, int *p);
extern void func_ov112_0229f6d4(UnkStruct_0229f7f0 *self, int val);
extern void func_ov112_0229fab4(UnkStruct_0229f7f0 *self);

void func_ov112_0229f7f0(UnkStruct_0229f7f0 *self, int param1, int param2)
{
    int a, lim;
    if (param2 < 0x38) {
        param2 = 0x38;
    }
    if (param2 >= 0x88) {
        param2 = 0x87;
    }
    self->unk_98 = param1;
    self->unk_9C = param2;
    a = (self->unk_9C - 0x28) >> 4;
    lim = self->unk_94;
    if (a > lim) {
        a = lim;
    }
    self->unk_9C = (a << 4) + 0x28;
    func_ov112_0229f6d4(self, func_ov112_0229f84c(self, a, &self->unk_98));
    func_ov112_0229fab4(self);
}
