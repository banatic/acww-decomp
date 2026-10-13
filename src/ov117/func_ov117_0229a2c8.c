/* func_ov117_0229a2c8 @ 0x0229a2c8, 0x22 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a2c8 {
    short a;
    short b;
    char c;
};

void func_ov117_0229a2c8(struct UnkStruct_0229a2c8 *arr)
{
    unsigned int i;
    for (i = 0; i < 17; i++) {
        arr[i].a = -1;
        arr[i].b = -1;
        arr[i].c = 0;
    }
}
