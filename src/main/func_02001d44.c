/* func_02001d44 @ 0x02001d44, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    char pad[0x12];
    unsigned short flags;
} data_0213fe74;

void func_02001d44(int cond)
{
    unsigned short mask;
    unsigned short v;

    if (cond != 0) {
        mask = 4;
    } else {
        mask = 0x100;
    }

    v = data_0213fe74.flags;
    v |= mask;
    data_0213fe74.flags = v;
}
