/* func_ov104_0229cc30 @ 0x0229cc30, 0x84 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229cc30 {
    char pad_00[0xB8];
    unsigned char unk_B8;
};

extern void func_ov104_0229c344(struct UnkStruct_0229cc30 *a, int x);
extern int func_ov104_0229da80(struct UnkStruct_0229cc30 *a, unsigned char b);
extern int func_ov104_0229da70(struct UnkStruct_0229cc30 *a, unsigned char b);
extern int func_ov104_0229da5c(struct UnkStruct_0229cc30 *a, unsigned char b);
extern void func_ov104_0229cdf0(struct UnkStruct_0229cc30 *a, int b, int c);
extern void func_ov104_0229cd18(struct UnkStruct_0229cc30 *a, int b, int c);
extern void func_ov104_0229ccb4(struct UnkStruct_0229cc30 *a, int b);

int func_ov104_0229cc30(struct UnkStruct_0229cc30 *a, int b, int c)
{
    unsigned char initial = a->unk_B8;
    func_ov104_0229c344(a, 0x30);
    if (b == 0) {
        return 0;
    }

    if (func_ov104_0229da80(a, a->unk_B8)) {
        func_ov104_0229cdf0(a, b, c);
    } else if (func_ov104_0229da70(a, a->unk_B8)) {
        func_ov104_0229cd18(a, b, c);
    } else if (func_ov104_0229da5c(a, a->unk_B8)) {
        func_ov104_0229ccb4(a, b);
    }

    if (initial != a->unk_B8) {
        return 1;
    }
    return 0;
}
