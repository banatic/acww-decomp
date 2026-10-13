/* func_ov105_0229ec90 @ 0x0229ec90, 0x26 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ec90 {
    char pad_00[0x9c];
    int unk_9C;
};

extern int func_ov002_02207f3c(struct UnkStruct_0229ec90 *obj, int a);
extern void func_ov105_0229ec68(struct UnkStruct_0229ec90 *obj);
extern int func_ov002_02207f60(struct UnkStruct_0229ec90 *obj);

void func_ov105_0229ec90(struct UnkStruct_0229ec90 *obj)
{
    if (func_ov002_02207f3c(obj, -1)) {
        func_ov105_0229ec68(obj);
    }
    obj->unk_9C = func_ov002_02207f60(obj);
}
