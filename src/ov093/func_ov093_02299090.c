/* func_ov093_02299090 @ 0x02299090, 0x28 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[4];
    unsigned char unk_04;
    char pad_05[0x19e0 - 5];
    char arr[26][0x6c];
} UnkStruct_02299090;

void *func_ov093_02299090(UnkStruct_02299090 *obj)
{
    if (obj->unk_04 >= 26) {
        return &obj->arr[25];
    } else {
        obj->unk_04++;
        return &obj->arr[obj->unk_04 - 1];
    }
}
