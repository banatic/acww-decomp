/* func_020bc6f4 @ 0x020bc6f4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020bc6f4 {
    char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc6f4;

extern void func_020bca80(UnkStruct_020bc6f4 *ptr, int a, int b, int c);
extern void func_020bc9c4(UnkStruct_020bc6f4 *ptr, int a);

void func_020bc6f4(UnkStruct_020bc6f4 *ptr)
{
    int field = ptr->unk_2F30;
    if (field < 0) {
        func_020bca80(ptr, 0, 100, 150);
    } else if (field == 0) {
        func_020bc9c4(ptr, 20);
    }
}
