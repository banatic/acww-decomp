/* talk_object_10: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02067af8 @ 0x02067af8, 0x24 bytes, Thumb
 * func_02067ac0 @ 0x02067ac0, 0x38 bytes, Thumb
 * func_02067ab0 @ 0x02067ab0, 0x10 bytes, Thumb
 */

struct UnkStruct_02067ac0 {
    unsigned char pad_00[0x18ac];
    unsigned char arr1[4][92];
    int arr2[4];
};

extern void func_020a81e0(void *ptr);
extern void func_020a8c1c(int arg);

void func_02067af8(void *ptr)
{
    int i;
    for (i = 0; i < 11; i++) {
        func_020a81e0((char *) ptr + 0x14b8 + i * 0x5c);
    }
}

void func_02067ac0(struct UnkStruct_02067ac0 *a)
{
    int i;
    for (i = 0; i < 4; i++) {
        func_020a81e0(a->arr1[i]);
        a->arr2[i] = 7;
    }
}

void func_02067ab0(int arg)
{
    func_020a8c1c(arg + 0x1C70);
}
