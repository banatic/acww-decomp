/* func_ov002_02208090 @ 0x02208090, 0x6 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char flags;
} UnkStruct_02208090;

void func_ov002_02208090(UnkStruct_02208090 *p, unsigned char v)
{
    p->flags = v;
}
