/* func_ov003_02212bf4 @ 0x02212bf4, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02212bf4 {
    int a;
    int b;
    int c;
    short d;
    char e;
    char unk_0F;
};

void func_ov003_02212bf4(struct UnkStruct_02212bf4 *dst, const struct UnkStruct_02212bf4 *src, short d, char e)
{
    dst->a = src->a;
    dst->b = src->b;
    dst->c = src->c;
    dst->d = d;
    dst->e = e;
    dst->unk_0F = 0;
}
