/* func_ov002_022085e8 @ 0x022085e8, 0x38 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022085e8 {
    char pad_00[0xc];
    int unk_0C;
    int unk_10;
};

extern int func_ov002_022087ec(struct UnkStruct_022085e8 *a, int b);
extern void func_ov002_02208348(struct UnkStruct_022085e8 *a, int b);

void func_ov002_022085e8(struct UnkStruct_022085e8 *a, int b)
{
    a->unk_0C = a->unk_10 - func_ov002_022087ec(a, a->unk_10);
    switch (b) {
        case 0:
            func_ov002_02208348(a, 2);
            break;
        case 1:
            func_ov002_02208348(a, 0);
            break;
    }
}
