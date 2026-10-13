/* func_ov048_02261608 @ 0x02261608, 0x38 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02261608 {
    char pad_00[0xb4];
    int unk_B4;
};

extern int func_ov048_022614ac(struct UnkStruct_02261608 *obj);
extern void func_020eb9fc(int value);
extern int func_0209fdf8(int value);
extern void func_ov048_022616b8(struct UnkStruct_02261608 *obj, int value);

void func_ov048_02261608(struct UnkStruct_02261608 *obj)
{
    int ret = func_ov048_022614ac(obj);
    if (ret) {
        func_020eb9fc(ret);
        func_ov048_022616b8(obj, obj->unk_B4 + 1);
    } else if (func_0209fdf8(ret)) {
        func_ov048_022616b8(obj, obj->unk_B4 + 1);
    }
}
