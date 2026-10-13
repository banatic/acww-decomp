/* func_02001d28 @ 0x02001d28, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    unsigned char pad[0x12];
    unsigned short val;
} data_0213fe74;

void func_02001d28(unsigned int a)
{
    unsigned short mask;
    if (a != 0) {
        mask = 8;
    } else {
        mask = 0x200;
    }
    data_0213fe74.val |= mask;
}
