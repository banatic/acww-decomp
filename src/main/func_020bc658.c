/* func_020bc658 @ 0x020bc658, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *s, int a, int b, int c);
extern void func_020bc9c4(void *s, int a);
extern void func_020bcd30(void *s);

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc658;

void func_020bc658(UnkStruct_020bc658 *s)
{
    int val;

    val = s->unk_2F30;
    if (val < 0) {
        func_020bca80(s, 0, 100, 0);
    } else {
        if (val == 0) {
            func_020bc9c4(s, 0x11);
        }
    }
    func_020bcd30(s);
}
