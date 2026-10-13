/* func_ov002_02209c78 @ 0x02209c78, 0x1c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a40c(void *obj, int arg);
extern int data_ov002_0220bc6c;

struct UnkStruct_02209c78 {
    void *unk_00;
};

struct UnkStruct_02209c78 *func_ov002_02209c78(struct UnkStruct_02209c78 *obj)
{
    func_ov002_0220a40c(obj, 1);
    obj->unk_00 = &data_ov002_0220bc6c;
    return obj;
}
