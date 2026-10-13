/* func_ov133_0229ad88 @ 0x0229ad88, 0x12 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ad88 {
    unsigned char pad_00[0x98];
    unsigned short flags;
};

int func_ov133_0229ad88(struct UnkStruct_0229ad88 *p, unsigned int mask)
{
    if ((p->flags & mask) == 0) {
        return 0;
    }
    return 1;
}
