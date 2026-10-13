/* func_0206e7bc @ 0x0206e7bc, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[4];
    char *unk_10;
    unsigned int unk_14;
    char *unk_18;
} UnkStruct_0206e7bc;

extern void func_0206e778(UnkStruct_0206e7bc *a, unsigned int i);

char *func_0206e7bc(UnkStruct_0206e7bc *a, unsigned int i)
{
    if (a->unk_10 != 0) {
        return a->unk_10 + a->unk_08 * i;
    }
    if (a->unk_14 == (i >> 3)) {
        return a->unk_18 + a->unk_08 * (i & 7);
    }
    if (a->unk_18 == 0) {
        goto ret0;
    }
    func_0206e778(a, i);
    {
        int off = a->unk_08 * (i & 7);
        a->unk_14 = i >> 3;
        return a->unk_18 + off;
    }
ret0:
    return 0;
}
