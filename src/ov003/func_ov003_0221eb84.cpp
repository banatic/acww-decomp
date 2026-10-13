/* func_ov003_0221eb84 @ 0x0221eb84, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221eb84 {
    unsigned char a, b, c, d;
};
struct UnkStruct_0221eb84_2 {
    char pad_00[0x2b4];
    int unk_2B4;
};

extern "C" void func_0209def4(struct UnkStruct_0221eb84 *);
extern "C" void *func_020984e8(void);
extern "C" int func_020a12e8(void);
extern "C" int func_02099020(void *, int);
extern "C" int func_ov003_0221eb48(struct UnkStruct_0221eb84_2 *);
extern "C" int func_020af9f0(void *);
extern "C" int data_021f395c;

extern "C" int func_ov003_0221eb84(struct UnkStruct_0221eb84_2 *o)
{
    struct UnkStruct_0221eb84 t;
    func_0209def4(&t);
    if (o->unk_2B4 == -1) {
        if (t.b >= 8 && t.b < 0x17) {
            return 1;
        }
        return 0;
    }
    void *h = func_020984e8();
    if (func_020a12e8() || (h && func_02099020(h, 0x23))) {
        return 0;
    }
    if (h && func_02099020(h, 1)) {
        return 1;
    }
    if (func_ov003_0221eb48(o)) {
        return 0;
    }
    if (t.b < 8 || t.b >= 0x17) {
        return 0;
    }
    if (func_020af9f0(&data_021f395c)) {
        return 0;
    }
    return 1;
}