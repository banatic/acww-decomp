/* func_ov117_0229a280 @ 0x0229a280, 0x24 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a280 {
    short a;
    short b;
    char c;
};

struct UnkStruct_0229a280 *func_ov117_0229a280(struct UnkStruct_0229a280 *arr, unsigned int i)
{
    if (i < 0x11) {
        if (arr[i].a != -1) {
            arr += i;
            if (arr->b != -1) {
                return arr;
            }
        }
        return 0;
    }
    return 0;
}
