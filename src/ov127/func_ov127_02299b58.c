/* func_ov127_02299b58 @ 0x02299b58, 0x20 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299b58 {
    char pad_00[0x2824];
    short unk_2824;
} UnkStruct_02299b58;

extern int func_ov127_02299868(UnkStruct_02299b58 *, int);

int func_ov127_02299b58(UnkStruct_02299b58 *base, int delta)
{
    base->unk_2824 = (base->unk_2824 + delta) & 0x1ff;
    return func_ov127_02299868(base, 1);
}
