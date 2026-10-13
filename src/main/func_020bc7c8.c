/* func_020bc7c8 @ 0x020bc7c8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} Struct020bc7c8;

extern void func_020bca80(Struct020bc7c8 *ptr, int a, int b, int c);
extern void func_020bc9c4(Struct020bc7c8 *ptr, int value);
extern void func_020bcb84(Struct020bc7c8 *ptr);

void func_020bc7c8(Struct020bc7c8 *ptr)
{
    if (ptr->unk_2F30 < 0) {
        func_020bca80(ptr, 100, 150, 600);
    } else if (ptr->unk_2F30 == 0) {
        func_020bc9c4(ptr, 20);
    }
    func_020bcb84(ptr);
}
