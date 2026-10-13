/* func_ov117_0229a26c @ 0x0229a26c, 0x12 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a26c {
    unsigned char pad_00[4];
    unsigned char b;
    unsigned char c;
};

unsigned char func_ov117_0229a26c(struct UnkStruct_0229a26c *arr, unsigned int i)
{
    if (i < 17) {
        return arr[i].b;
    } else {
        return arr[0].b;
    }
}
