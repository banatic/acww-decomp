/* func_020b7db0 @ 0x020b7db0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020b7db0 UnkStruct_020b7db0;
typedef struct UnkStruct_020b7db0_2 UnkStruct_020b7db0_2;
struct UnkStruct_020b7db0 {
    char pad_00[0x20];
    void *unk_20;
};
struct UnkStruct_020b7db0_2 {
    char pad_00[0x18];
    void *unk_18;
};

int func_020b7db0(UnkStruct_020b7db0 *a, UnkStruct_020b7db0_2 *b)
{
    void *tmp;
    b->unk_18 = 0;
    tmp = a->unk_20;
    if (tmp == 0) {
        a->unk_20 = b;
        return 1;
    } else {
        b->unk_18 = tmp;
        a->unk_20 = b;
        return 1;
    }
}
