/* func_020bda88 @ 0x020bda88, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02065268(int);
extern int func_020644cc(int);

struct UnkStruct_020bda88 {
    char pad_00[0x2f10];
    int unk_2F10;
};

void func_020bda88(struct UnkStruct_020bda88 *p)
{
    if (p->unk_2F10 <= 0) {
        p->unk_2F10 = 0x32;
    }
    p->unk_2F10 = p->unk_2F10 - 1;
    if (p->unk_2F10 > 0) {
        return;
    }
    func_02065268(0);
    p->unk_2F10 = func_020644cc(0xc8) + 0xa;
}
