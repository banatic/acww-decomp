/* func_ov003_02219e98 @ 0x02219e98, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02219e98 {
    int unk_00;
    int unk_04;
};
struct UnkStruct_02219e98_2 {
    char pad_00[0x12c];
    struct UnkStruct_02219e98 *ptr;
};
extern void func_ov003_0221a004(void *obj, int arg);

void func_ov003_02219e98(struct UnkStruct_02219e98_2 *obj)
{
    if (obj->ptr != 0 && obj->ptr->unk_04 != 0) {
        func_ov003_0221a004(obj, 2);
    }
}
