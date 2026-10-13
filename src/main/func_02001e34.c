/* func_02001e34 @ 0x02001e34, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    unsigned char pad[0x11];
    unsigned char flag;
} data_0213fe74;
extern struct {
    unsigned char pad[0x40];
    unsigned int val1;
    unsigned int val2;
} data_0213fdf4;

void func_02001e34(unsigned int param1, unsigned int param2)
{
    data_0213fe74.flag |= 8;
    data_0213fdf4.val1 = param1;
    data_0213fdf4.val2 = param2;
}
