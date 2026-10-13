/* func_ov142_0229a45c @ 0x0229a45c, 0x78 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9C];
    int unk_9C;
    int unk_A0;
} UnkStruct_0229a45c;

extern void func_ov142_0229a4d4(UnkStruct_0229a45c *obj, int value);
extern void func_ov142_02299a54(UnkStruct_0229a45c *obj);

void func_ov142_0229a45c(UnkStruct_0229a45c *obj)
{
    if (obj->unk_9C == obj->unk_A0) {
        return;
    }
    if (obj->unk_9C > obj->unk_A0) {
        obj->unk_9C = obj->unk_9C - 6;
        if (obj->unk_9C < obj->unk_A0) {
            obj->unk_9C = obj->unk_A0;
        }
    } else {
        obj->unk_9C = obj->unk_9C + 6;
        if (obj->unk_9C > obj->unk_A0) {
            obj->unk_9C = obj->unk_A0;
        }
    }
    func_ov142_0229a4d4(obj, obj->unk_9C);
    func_ov142_02299a54(obj);
}
