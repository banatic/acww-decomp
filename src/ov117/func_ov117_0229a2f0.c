/* func_ov117_0229a2f0 @ 0x0229a2f0, 0x22 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a2f0 {
    short a;
    short b;
    char c;
};

extern void func_ov117_0229a2c8(struct UnkStruct_0229a2f0 *arr);

struct UnkStruct_0229a2f0 *func_ov117_0229a2f0(struct UnkStruct_0229a2f0 *arr)
{
    struct UnkStruct_0229a2f0 *p = arr;
    do {
        p->a = 0;
        p->b = 0;
        p++;
    } while (p != arr + 17);
    func_ov117_0229a2c8(arr);
    return arr;
}
