/* func_020bb30c @ 0x020bb30c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bb7e0(void *obj, int a, int b);
extern int _s32_div_f(int, int);

struct UnkStruct_020bb30c {
    char pad_00[0x120c];
    int unk_120C;
    char pad_1210[0x318];
    int unk_1528;
    char pad_152C[0x60];
    int unk_158C;
    int unk_1590;
};

void func_020bb30c(struct UnkStruct_020bb30c *p)
{
    p->unk_1590++;
    if (p->unk_1590 >= 0x2a8) {
        func_020bb7e0(p, p->unk_1528, p->unk_1528);
        p->unk_158C = 3;
    }
    p->unk_120C = _s32_div_f(p->unk_1590 << 5, 0x2a8);
}
