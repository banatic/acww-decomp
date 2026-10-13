/* func_ov075_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov075_022799fc;
extern void func_ov075_02278ba0(void *);
extern void func_0202ee5c(void *);

struct UnkStruct_02278a00 {
    char *unk_00;
};

void *func_ov075_02278a00(struct UnkStruct_02278a00 *obj)
{
    obj->unk_00 = &data_ov075_022799fc;
    func_ov075_02278ba0((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
