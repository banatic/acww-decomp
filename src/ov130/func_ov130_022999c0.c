/* func_ov130_022999c0 @ 0x022999c0, 0x24 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

typedef char Elem[108];
typedef struct {
    char pad_00[6];
    unsigned char count;
    char pad_07[37];
    Elem arr[5];
} UnkStruct_022999c0;

Elem *func_ov130_022999c0(UnkStruct_022999c0 *obj)
{
    if (obj->count < 5) {
        goto body;
    }
    return &obj->arr[4];
body:
    obj->count++;
    return &obj->arr[obj->count - 1];
}
