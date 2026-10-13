/* func_ov003_0221c0a0 @ 0x0221c0a0, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221c0a0 {
    unsigned char pad_00[0x10A];
    unsigned char cond;
    unsigned char pad_10B[0x21];
    int *data;
};

extern void func_ov003_0221bfa8(struct UnkStruct_0221c0a0 *a, int value);

void func_ov003_0221c0a0(struct UnkStruct_0221c0a0 *a)
{
    switch (a->cond) {
        case 2:
            a->data[5] = 1;
            func_ov003_0221bfa8(a, 4);
            break;
        case 3:
        case 0x32:
            func_ov003_0221bfa8(a, 6);
    }
}
