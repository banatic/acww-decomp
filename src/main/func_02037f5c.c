/* func_02037f5c @ 0x02037f5c, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02037f5c UnkStruct_02037f5c;
struct UnkStruct_02037f5c {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad_0C[12];
    int arr[2];
};

void func_02037f5c(UnkStruct_02037f5c *p)
{
    int i = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
    for (; i < 2; i++) {
        p->arr[i] = 0;
    }
}
