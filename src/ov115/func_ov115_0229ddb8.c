/* func_ov115_0229ddb8 @ 0x0229ddb8, 0x18 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ddb8 {
    unsigned char pad_00[0x1428];
    unsigned short flags;
};

int func_ov115_0229ddb8(struct UnkStruct_0229ddb8 *p, unsigned short mask)
{
    return (p->flags & mask) != 0;
}
