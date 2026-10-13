/* func_ov093_02299048 @ 0x02299048, 0x48 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *ptr);
extern void func_020b9ccc(void *ptr);

struct UnkStruct_02299048 {
    char data[0x6c];
};
struct UnkStruct_02299048_2 {
    char data[0x24];
};

struct UnkStruct_02299048_3 {
    unsigned int unk_00;
    unsigned char flag;
    unsigned char pad_05[0x19e0 - 5];
    struct UnkStruct_02299048 arr1[26];
    struct UnkStruct_02299048_2 arr2[2];
};

void func_ov093_02299048(struct UnkStruct_02299048_3 *self)
{
    int i;
    self->flag = 0;
    for (i = 0; i < 26; i++) {
        func_02070b84(&self->arr1[i]);
    }
    for (i = 0; i < 2; i++) {
        func_020b9ccc(&self->arr2[i]);
    }
}
