/* func_020bc954 @ 0x020bc954, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020bc954 {
    char pad_00[0x2f30];
    int unk_2F30;
};

extern void func_020bca80(struct UnkStruct_020bc954 *ptr, int a, int b, int c);
extern void func_020bc9c4(struct UnkStruct_020bc954 *ptr, int d);
extern void func_020bcd30(struct UnkStruct_020bc954 *ptr);

void func_020bc954(struct UnkStruct_020bc954 *ptr)
{
    if (ptr->unk_2F30 < 0) {
        func_020bca80(ptr, 100, 100, 500);
    } else if (ptr->unk_2F30 == 0) {
        func_020bc9c4(ptr, 20);
    }
    func_020bcd30(ptr);
}
