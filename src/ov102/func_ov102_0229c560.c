/* func_ov102_0229c560 @ 0x0229c560, 0x124 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c560 {
    char pad_00;
} UnkStruct_0229c560;

typedef struct UnkStruct_0229c560_2 {
    char pad_00[0x2274];
    UnkStruct_0229c560 unk_2274;
    char pad1[0x25a5 - 0x2274 - sizeof(UnkStruct_0229c560)];
    unsigned char unk_25A5;
} UnkStruct_0229c560_2;

extern void func_ov102_0229c288(UnkStruct_0229c560_2 *p, int arg);
extern int func_ov102_0229d464(UnkStruct_0229c560_2 *p, int byte);
extern int func_ov102_0229d454(UnkStruct_0229c560_2 *p, int byte);
extern int func_ov102_0229d444(UnkStruct_0229c560_2 *p, int byte);
extern int func_ov102_0229d438(UnkStruct_0229c560_2 *p, int byte);
extern void func_ov102_0229c8bc(UnkStruct_0229c560_2 *p, int a, int b);
extern void func_ov102_0229c790(UnkStruct_0229c560_2 *p, int a, int b);
extern void func_ov102_0229c740(UnkStruct_0229c560_2 *p, int a);
extern void func_ov102_0229c684(UnkStruct_0229c560_2 *p, int a, int b);
extern void func_ov102_0229c298(UnkStruct_0229c560_2 *p, int arg);

extern void func_ov002_0220a374(UnkStruct_0229c560 *p, int arg);
extern void func_ov002_0220a314(UnkStruct_0229c560 *p);
extern void func_ov002_0220a2b4(UnkStruct_0229c560 *p);
extern void func_0208e4c0(UnkStruct_0229c560 *p, int arg);

int func_ov102_0229c560(UnkStruct_0229c560_2 *self, int a, int b)
{
    unsigned char state;
    state = self->unk_25A5;
    func_ov102_0229c288(self, 0x30);
    func_ov102_0229c288(self, 0x100);
    if (a == 0) {
        return 0;
    }

    if (func_ov102_0229d464(self, self->unk_25A5)) {
        func_ov102_0229c8bc(self, a, b);
    } else if (func_ov102_0229d454(self, self->unk_25A5)) {
        func_ov102_0229c790(self, a, b);
        if (b == 1) {
            if (func_ov102_0229d444(self, self->unk_25A5)) {
                func_ov002_0220a374(&self->unk_2274, 1);
            }
        }
    } else if (func_ov102_0229d438(self, self->unk_25A5)) {
        func_ov102_0229c740(self, a);
    } else if (func_ov102_0229d444(self, self->unk_25A5)) {
        func_ov102_0229c684(self, a, b);
        if (b == 1) {
            if (!func_ov102_0229d444(self, self->unk_25A5)) {
                func_0208e4c0(&self->unk_2274, 4);
            }
        }
    }

    if (func_ov102_0229d438(self, self->unk_25A5) != func_ov102_0229d438(self, state)) {
        if (func_ov102_0229d438(self, self->unk_25A5)) {
            func_ov002_0220a314(&self->unk_2274);
        } else {
            func_ov002_0220a2b4(&self->unk_2274);
        }
        func_ov102_0229c298(self, 0x100);
    }

    if (state != self->unk_25A5) {
        return 1;
    } else {
        return 0;
    }
}
