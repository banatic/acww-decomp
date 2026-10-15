/* func_ov003_0220d268 @ 0x0220d268, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0220d268 {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_0220d268;

extern int func_02010718(UnkStruct_0220d268 *obj);
extern int func_02008258(UnkStruct_0220d268 *obj, int val);
extern int func_0200d1a0(UnkStruct_0220d268 *obj, int a, int b, int c);
extern int func_02010538(UnkStruct_0220d268 *obj);

int func_ov003_0220d268(UnkStruct_0220d268 *obj)
{
    if (func_02010718(obj) > 0) {
        obj->unk_7FC = func_02008258(obj, obj->unk_7F0);
        return func_0200d1a0(obj, 0, 1, -1);
    } else {
        return func_02010538(obj);
    }
}
