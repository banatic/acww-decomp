/* func_02088aac @ 0x02088aac, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char flags;
} UnkStruct_02088aac;
void func_02088aac(UnkStruct_02088aac *p)
{
    p->flags |= 0x40;
}
