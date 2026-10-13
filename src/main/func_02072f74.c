/* func_02072f74 @ 0x02072f74, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct BitField {
    unsigned char low : 4;
    unsigned char high : 4;
};

struct UnkStruct_02072f74 {
    unsigned char pad_00[0x32];
    struct BitField bits;
};

unsigned char func_02072f74(struct UnkStruct_02072f74 *o)
{
    return (unsigned char) (o->bits.high & 0xF);
}
