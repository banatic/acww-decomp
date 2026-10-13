/* func_ov003_0221f244 @ 0x0221f244, 0x2a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056ffc(void *p);

struct UnkStruct_0221f244 {
    char pad_00[0x8];
    unsigned int val;
    char pad_0C[0xC];
    unsigned int *ptr;
    char pad_1C[0x4];
};

struct UnkStruct_0221f244_2 {
    char pad_00[0xA8];
    struct UnkStruct_0221f244 arr[2];
};

int func_ov003_0221f244(struct UnkStruct_0221f244_2 *out)
{
    struct UnkStruct_0221f244 *p;
    for (p = out->arr; p < &out->arr[2]; p++) {
        func_02056ffc(p);
        *p->ptr = p->val;
    }
    return 1;
}
