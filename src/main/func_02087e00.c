/* func_02087e00 @ 0x02087e00, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    unsigned char flags;
} UnkStruct_02087e00;
void func_02087e00(UnkStruct_02087e00 *p)
{
    p->flags &= ~2;
}
