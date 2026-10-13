/* func_0203c1e0 @ 0x0203c1e0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203c1e0 {
    char pad_00[0x178];
    int unk_178;
    int unk_17C;
};

int func_0203c1e0(struct UnkStruct_0203c1e0 *A, int *B)
{
    int val = *B;
    if (val < A->unk_178 + 0x5000) {
        return 1;
    }
    if (val > A->unk_17C - 0x5000) {
        return 2;
    }
    return 0;
}
