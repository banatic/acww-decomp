/* func_0200fef0 @ 0x0200fef0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020431c8(int);
extern void func_020431b8(int);

struct Struct0200fef0 {
    unsigned char pad_00[0x810];
    int unk_810;
};

void func_0200fef0(struct Struct0200fef0 *p)
{
    int ret;

    if (p->unk_810 == -1) {
        return;
    }

    ret = func_020431c8(p->unk_810);

    if (ret != 1 && ret != 2) {
        return;
    }

    func_020431b8(p->unk_810);
    p->unk_810 = -1;
}
