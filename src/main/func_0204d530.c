/* func_0204d530 @ 0x0204d530, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0204d530 {
    char pad_00[0x54];
    int *arr;
    int limit;
};

void func_0204d530(struct UnkStruct_0204d530 *obj, int value, int index)
{
    int *arr = obj->arr;
    if (arr != 0) {
        if (index < obj->limit) {
            arr[index] = value;
        }
    }
}
