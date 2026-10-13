/* func_020e9fa8 @ 0x020e9fa8, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_02101e20(int arg);

struct S020e9fa8 {
    char pad_00[0x14];
    int unk_14;
};

void func_020e9fa8(struct S020e9fa8 *s)
{
    func_02101e20(s->unk_14);
    s->unk_14 = 0;
}
