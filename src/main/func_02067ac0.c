/* func_02067ac0 @ 0x02067ac0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a81e0(void *);

struct UnkStruct_02067ac0 {
    unsigned char pad_00[0x18ac];
    unsigned char arr1[4][92];
    int arr2[4];
};

void func_02067ac0(struct UnkStruct_02067ac0 *a)
{
    int i;
    for (i = 0; i < 4; i++) {
        func_020a81e0(a->arr1[i]);
        a->arr2[i] = 7;
    }
}
