/* func_02088aa0 @ 0x02088aa0, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char flags;
} UnkStruct_02088aa0;
void func_02088aa0(UnkStruct_02088aa0 *p)
{
    p->flags &= ~0x40;
}
