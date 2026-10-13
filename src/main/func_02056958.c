/* func_02056958 @ 0x02056958, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02056958 {
    unsigned char pad_00[0x23];
    unsigned char flag;
};

int func_02056958(struct UnkStruct_02056958 *p)
{
    return (p->flag & 1) ? 1 : 0;
}
