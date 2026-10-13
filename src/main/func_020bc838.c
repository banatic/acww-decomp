/* func_020bc838 @ 0x020bc838, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *arg, int a, int b, int c);
extern void func_020bc9c4(void *arg, int a);
extern void func_020bcb84(void *arg);

typedef struct {
    unsigned char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc838;

void func_020bc838(UnkStruct_020bc838 *arg)
{
    int val;
    val = arg->unk_2F30;
    if (val < 0) {
        func_020bca80(arg, 30, 150, 0x190);
    } else {
        if (val == 0) {
            func_020bc9c4(arg, 20);
        }
    }
    func_020bcb84(arg);
}
