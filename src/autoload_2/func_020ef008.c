/* func_020ef008 @ 0x020ef008, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ef008 {
    char pad_00[0xc];
    int unk_0C;
};

extern void func_020eef80(struct UnkStruct_020ef008 *p, int b);
extern void func_020eefd4(struct UnkStruct_020ef008 *p);

int func_020ef008(struct UnkStruct_020ef008 *p, int b)
{
    func_020eef80(p, b);
    if (b != 0) {
        func_020eefd4(p);
    }
    p->unk_0C = 0;
    return 0;
}
