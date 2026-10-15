/* func_ov103_0229c350 @ 0x0229c350, 0x50 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c350 {
    unsigned char pad_00[0x2da4];
    unsigned char flags;
};

extern void func_ov103_0229c2d4(struct UnkStruct_0229c350 *self, int x);
extern int func_ov103_0229cdfc(struct UnkStruct_0229c350 *self, unsigned char x);
extern void func_ov103_0229c3a0(struct UnkStruct_0229c350 *self, int a, int b);

int func_ov103_0229c350(struct UnkStruct_0229c350 *self, int a1, int a2)
{
    unsigned char old = self->flags;

    func_ov103_0229c2d4(self, 0x30);
    if (a1 == 0) {
        return 0;
    }

    if (func_ov103_0229cdfc(self, self->flags) != 0) {
        func_ov103_0229c3a0(self, a1, a2);
    }

    return old != self->flags;
}
