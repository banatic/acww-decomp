/* func_02001d00 @ 0x02001d00, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1b];
    unsigned char value;
} unk_struct;
extern unk_struct data_0213fe74;
void func_02001d00(unsigned char param)
{
    data_0213fe74.value = param;
}
