/* func_ov096_0229c2dc @ 0x0229c2dc, 0xe bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x94];
    unsigned int unk_94;
} Struct_ov096_0229c2dc;

void func_ov096_0229c2dc(Struct_ov096_0229c2dc *s, unsigned int mask)
{
    s->unk_94 &= ~mask;
}
