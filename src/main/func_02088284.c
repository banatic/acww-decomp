/* func_02088284 @ 0x02088284, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xe];
    unsigned char flags;
} UnkStruct_02088284;
void func_02088284(UnkStruct_02088284 *p)
{
    p->flags &= ~0x20;
}
