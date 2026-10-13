/* func_020bc800 @ 0x020bc800, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *p, int a, int b, int c);
extern void func_020bc9c4(void *p, int a);
extern void func_020bcb84(void *p);

struct UnkStruct_020bc800 {
    char pad_00[0x2f30];
    int unk_2F30;
};

void func_020bc800(struct UnkStruct_020bc800 *p)
{
    int f = p->unk_2F30;
    if (f < 0) {
        func_020bca80(p, 60, 150, 500);
    } else if (f == 0) {
        func_020bc9c4(p, 20);
    }
    func_020bcb84(p);
}
