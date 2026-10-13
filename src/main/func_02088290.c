/* func_02088290 @ 0x02088290, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xe];
    unsigned char flags;
} UnkStruct_02088290;
void func_02088290(UnkStruct_02088290 *p)
{
    p->flags |= 0x20;
}
