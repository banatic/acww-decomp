/* func_02017dd8 @ 0x02017dd8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02017dd8 {
    char pad_00[0x98];
    unsigned char unk_98;
};

struct SomeOtherStruct {
    char pad_00[0x190];
    unsigned int unk_190;
};

void func_02019af0(struct UnkStruct_02017dd8 *, int);

void func_02017dd8(struct UnkStruct_02017dd8 *a, struct SomeOtherStruct *b)
{
    if (((b->unk_190 << 4) >> 16) == 0) {
        func_02019af0(a, 1);
        a->unk_98 = 0x14;
    }
}
