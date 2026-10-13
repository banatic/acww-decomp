/* func_ov145_02299648 @ 0x02299648, 0xe bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned short flags;
} UnkStruct_02299648;

void func_ov145_02299648(UnkStruct_02299648 *p, unsigned short mask)
{
    p->flags = p->flags & ~mask;
}
