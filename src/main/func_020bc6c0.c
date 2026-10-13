/* func_020bc6c0 @ 0x020bc6c0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *ptr, int a, int b, int c);
extern void func_020bc9c4(void *ptr, int a);
extern void func_020bcc70(void *ptr);

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc6c0;

void func_020bc6c0(UnkStruct_020bc6c0 *ptr)
{
    int field = ptr->unk_2F30;
    if (field < 0) {
        int zero = 0;
        func_020bca80(ptr, zero, 100, zero);
    } else if (field == 0) {
        func_020bc9c4(ptr, 15);
    }
    func_020bcc70(ptr);
}
