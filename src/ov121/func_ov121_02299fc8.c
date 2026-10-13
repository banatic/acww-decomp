/* func_ov121_02299fc8 @ 0x02299fc8, 0x16 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299fc8 {
    unsigned char pad_00[0xb1];
    unsigned char data;
};

int func_ov121_02299fc8(const struct UnkStruct_02299fc8 *p)
{
    unsigned char c = p->data;
    if (c >= 0x10 && c <= 0x17) {
        return c - 0x10;
    }
    return -1;
}
