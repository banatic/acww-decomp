/* func_020c0b30 @ 0x020c0b30, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020c0b30 {
    char pad_00[4];
    int unk_04;
    char pad_08[44];
    int unk_34;
} UnkStruct_020c0b30;

extern unsigned int data_021fbdd0;
extern int func_020c0e44(void *ptr);
extern void func_020c0bac(UnkStruct_020c0b30 *ptr);

void func_020c0b30(UnkStruct_020c0b30 *param)
{
    if ((data_021fbdd0 & 0x7f) == 0) {
        if (func_020c0e44(&param->unk_34) == 0) {
            param->unk_04 = 3;
        }
        func_020c0bac(param);
    }
}
