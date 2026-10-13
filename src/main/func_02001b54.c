/* func_02001b54 @ 0x02001b54, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x14];
    unsigned char value;
} Global;

extern Global data_0213fe74;

void func_02001b54(unsigned char arg)
{
    data_0213fe74.value = arg;
}
