/* func_ov003_0221e4a4 @ 0x0221e4a4, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221e4a4 {
    int a;
    int b;
    int c;
};

struct UnkStruct_0221e4a4_2 {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
};

extern int func_020310c8(int arg);
extern int func_ov003_02219a14(struct UnkStruct_0221e4a4 *p);
extern void func_020b2800(struct UnkStruct_0221e4a4_2 *self, int arg);

int func_ov003_0221e4a4(struct UnkStruct_0221e4a4_2 *self)
{
    struct UnkStruct_0221e4a4 s;
    s.a = self->unk_5C;
    s.b = func_020310c8(0);
    s.c = self->unk_64 + 0x2000;
    if (func_ov003_02219a14(&s) != 0) {
        func_020b2800(self, 3);
    }
    return 1;
}
