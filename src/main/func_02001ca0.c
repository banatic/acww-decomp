/* func_02001ca0 @ 0x02001ca0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe94[];
extern struct {
    char pad[0x12];
    unsigned short flags;
} data_0213fe74;

void func_02001ca0(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    data_0213fe94[3] = a;
    data_0213fe94[4] = b;
    data_0213fe94[5] = c;
    data_0213fe94[6] = d;
    data_0213fe74.flags |= 0x20;
}
