/* func_ov003_0221ff80 @ 0x0221ff80, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221ff80 {
    int unk_00;
    int arr[5];
    int unk_18;
    char unk_1C;
};

void func_ov003_0221ff80(struct UnkStruct_0221ff80 *p)
{
    unsigned int i = 0;
    unsigned int zero = i;
    for (; i < 5; i++) {
        p->arr[i] = zero;
    }
    p->unk_00 = zero;
    p->unk_18 = zero;
    p->unk_1C = zero;
}
