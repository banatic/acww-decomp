/* func_ov003_02222d68 @ 0x02222d68, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02222d8c(int a, unsigned int b, unsigned int *c);

typedef struct {
    unsigned char pad_00[4];
    unsigned int unk_04;
    unsigned char pad_08[0xcc - 8];
    unsigned int unk_CC;
    unsigned int unk_D0;
} UnkStruct_02222d68;

void func_ov003_02222d68(UnkStruct_02222d68 *obj, int arg2)
{
    unsigned int arr[2];
    arr[0] = obj->unk_CC;
    arr[1] = obj->unk_D0;
    func_ov003_02222d8c(arg2, obj->unk_04, arr);
}
