/* func_ov002_02208a14 @ 0x02208a14, 0x10 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x14];
    unsigned short flags;
} UnkStruct_02208a14;

int func_ov002_02208a14(UnkStruct_02208a14 *p, int mask)
{
    if (p->flags & mask) {
        return 1;
    }
    return 0;
}
