/* func_02088b80 @ 0x02088b80, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02088b80 {
    unsigned char pad_00[12];
    unsigned char value;
};

void func_02088b80(struct UnkStruct_02088b80 *p)
{
    p->value = p->value + 1;
    if (p->value > 12) {
        p->value = 12;
    }
}
