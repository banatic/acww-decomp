/* func_ov129_0229b7dc @ 0x0229b7dc, 0xe bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa4];
    unsigned short unk_A4;
} UnkStruct_0229b7dc;

void func_ov129_0229b7dc(UnkStruct_0229b7dc *p, unsigned short v)
{
    unsigned short tmp = p->unk_A4;
    tmp |= v;
    p->unk_A4 = tmp;
}
