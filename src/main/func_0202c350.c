/* func_0202c350 @ 0x0202c350, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202c350 {
    char pad_00[0x12c];
    int unk_12C;
};

extern int func_02081d64(int value);
extern void *func_02015e70(struct UnkStruct_0202c350 *obj, int value, int flag);
extern int data_020c8cf8;

int *func_0202c350(struct UnkStruct_0202c350 *obj)
{
    if (obj->unk_12C) {
        func_02015e70(obj, func_02081d64(obj->unk_12C), 1);
    }
    return &data_020c8cf8;
}
