/* func_02088b38 @ 0x02088b38, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02088b38 {
    unsigned char pad_00[0x10];
    unsigned char flag;
};

void func_02088b38(struct UnkStruct_02088b38 *s, int val)
{
    s->flag = (s->flag & ~1) | (val & 1);
}
