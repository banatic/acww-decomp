/* func_0206bf08 @ 0x0206bf08, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a92d8(void *obj, int arg);

struct UnkStruct_0206bf08 {
    char pad_00[0x2c];
    int unk_2C;
    int unk_30;
    char pad_34[0x4];
    unsigned char unk_38;
};

void func_0206bf08(struct UnkStruct_0206bf08 *obj)
{
    int v = obj->unk_2C;
    if (v == 1) {
        obj->unk_38 = 1;
        func_020a92d8(obj, 0);
    } else if (v == 2) {
        obj->unk_38 = 1;
        func_020a92d8(obj, obj->unk_30);
    }
}
