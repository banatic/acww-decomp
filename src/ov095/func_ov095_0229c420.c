/* func_ov095_0229c420 @ 0x0229c420, 0x28 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f608(void *self, int arg2);
extern int func_0206f5e4(int value);
extern void func_ov095_0229c22c(void *self, int result, int arg2, int zero);

struct Struct_ov095_0229c420 {
    char pad_00[0x16];
    volatile unsigned char unk_16;
};

void func_ov095_0229c420(struct Struct_ov095_0229c420 *self, int arg2)
{
    self->unk_16 = (unsigned char) func_0206f608(self, arg2);
    func_ov095_0229c22c(self, func_0206f5e4(self->unk_16), arg2, 0);
}
