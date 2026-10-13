/* func_02001afc @ 0x02001afc, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    unsigned char pad[0x15];
    unsigned char flag;
} data_0213fe74;

void func_02001afc(unsigned char mask)
{
    data_0213fe74.flag &= ~mask;
}
