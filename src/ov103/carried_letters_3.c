/* carried_letters_3: 2 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229c820 @ 0x0229c820, 0x48 bytes, Thumb
 * func_ov103_0229c810 @ 0x0229c810, 0x10 bytes, Thumb
 */

struct Ts {
    char pad_00[0x2da4];
    unsigned char unk_2DA4;
};

struct UnkStruct_0229c810 {
    char pad_00[0x2da4];
    unsigned char unk_2DA4;
};

extern int func_ov103_0229ccb4(void *p, int b);
extern int func_ov103_0229c2f4(void *p, int mode);
extern int func_ov103_0229cc80(struct UnkStruct_0229c810 *self, unsigned char byte);

int func_ov103_0229c820(struct Ts *p)
{
    int val;

    val = func_ov103_0229ccb4(p, p->unk_2DA4);
    if (func_ov103_0229c2f4(p, 0x20) != 0) {
        val += 0x100;
    } else if (func_ov103_0229c2f4(p, 0x10) != 0) {
        val -= 0x100;
    }
    val += 8;
    return val;
}

int func_ov103_0229c810(struct UnkStruct_0229c810 *self)
{
    return func_ov103_0229cc80(self, self->unk_2DA4);
}
