/* func_ov117_02299ca4 @ 0x02299ca4, 0x2c bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299ca4 {
    short x;
    short y;
    unsigned char z;
};

void func_ov117_02299ca4(struct UnkStruct_02299ca4 *src, struct UnkStruct_02299ca4 *dst)
{
    unsigned int i;
    for (i = 0; i < 17; i++) {
        dst[i].x = src[i].x;
        dst[i].y = src[i].y;
        dst[i].z = src[i].z;
    }
}
