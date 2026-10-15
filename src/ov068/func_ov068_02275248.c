/* func_ov068_02275248 @ 0x02275248, 0x30 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov068_02278140;
extern char data_ov068_022780b0;
extern void *func_0202de4c(void *p);
extern void *func_0202e5e0(void *p);

typedef struct {
    void *unk_00;
    char pad_04[0x89c - 4];
    void *unk_89C;
} UnkStruct_02275248;

void *func_ov068_02275248(UnkStruct_02275248 *obj)
{
    obj->unk_00 = &data_ov068_02278140;
    obj->unk_89C = &data_ov068_022780b0;
    func_0202de4c((void *) &obj->unk_89C);
    func_0202e5e0(obj);
    return obj;
}
