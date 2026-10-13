/* func_ov110_0229c2a8 @ 0x0229c2a8, 0xe bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x94];
    unsigned int unk_94;
} UnkStruct_0229c2a8;

void func_ov110_0229c2a8(UnkStruct_0229c2a8 *obj, unsigned int mask)
{
    obj->unk_94 &= ~mask;
}
