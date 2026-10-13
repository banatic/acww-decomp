/* func_020bc870 @ 0x020bc870, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *p, int a, int b, int c);
extern void func_020bc9c4(void *p, int a);
extern void func_020bcc70(void *p);

struct Struct020bc870 {
    char pad_00[0x2f30];
    int unk_2F30;
};

void func_020bc870(struct Struct020bc870 *p)
{
    int f;
    f = p->unk_2F30;
    if (f < 0) {
        func_020bca80(p, 0x12c, 0x64, 0x258);
    } else if (f == 0) {
        func_020bc9c4(p, 0x14);
    }
    func_020bcc70(p);
}
