/* func_ov003_0221ffb4 @ 0x0221ffb4, 0xc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221ffb4 {
    char pad_00[0x10];
    int arr[4];
};

int func_ov003_0221ffb4(struct UnkStruct_0221ffb4 *s, int idx)
{
    return s->arr[idx & 3];
}
