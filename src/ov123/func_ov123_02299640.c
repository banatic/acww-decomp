/* func_ov123_02299640 @ 0x02299640, 0xe bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02299640;

typedef struct {
    char pad_00[0x9c];
    unsigned int unk_9C;
} UnkStruct_02299640;

void func_ov123_02299640(UnkStruct_02299640 *p, unsigned int v)
{
    p->unk_9C = p->unk_9C | v;
}
