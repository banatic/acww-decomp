/* func_ov075_02278ba0 @ 0x02278ba0, 0x18 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02278ba0 {
    void *unk_00;
};

extern char data_ov075_0227996c;
extern void func_0202eb20(struct UnkStruct_02278ba0 *obj);

struct UnkStruct_02278ba0 *func_ov075_02278ba0(struct UnkStruct_02278ba0 *obj)
{
    obj->unk_00 = &data_ov075_0227996c;
    func_0202eb20(obj);
    return obj;
}
