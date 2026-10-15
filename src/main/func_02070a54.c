/* func_02070a54 @ 0x02070a54, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02070a54 {
    unsigned char pad_00[0x38];
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char pad_3A[0x1E];
    unsigned int unk_58;
};

struct UnkStruct_02070a54_2 {
    unsigned char pad_00[0x68];
    struct UnkStruct_02070a54 *b;
};

extern void func_02070b84(struct UnkStruct_02070a54_2 *a);
extern struct UnkStruct_02070a54 *func_020a8fe8(int, int, int);

void func_02070a54(struct UnkStruct_02070a54_2 *a, int arg1, int arg2, int arg3, unsigned char arg4)
{
    if (a->b) {
        func_02070b84(a);
    }
    a->b = func_020a8fe8(arg1, arg2, 2);
    if (a->b) {
        a->b->unk_39 = arg4;
        a->b->unk_38 = (unsigned char) arg3;
        a->b->unk_58 = 2;
    }
}
