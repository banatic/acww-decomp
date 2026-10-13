/* func_02001a48 @ 0x02001a48, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    unsigned char pad[0x12];
    unsigned char flag12;
    unsigned char flag13;
} data_0213fe94;

void func_02001a48(void)
{
    data_0213fe94.flag13 = 0x1f;
    data_0213fe94.flag12 |= 4;
}
