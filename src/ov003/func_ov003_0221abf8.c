/* func_ov003_0221abf8 @ 0x0221abf8, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221a35c(void *obj, int value);

struct UnkStruct_0221abf8 {
    char pad_00[0x39c];
    int unk_39C;
};

int func_ov003_0221abf8(void *object, int flag)
{
    struct UnkStruct_0221abf8 *obj = object;
    if (obj->unk_39C < 7) {
        return func_ov003_0221a35c(obj, 3);
    }
    return 0;
}
