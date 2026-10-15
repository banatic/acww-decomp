/* func_ov003_0221ddbc @ 0x0221ddbc, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_02239254[];
extern char data_ov003_02239318[];
extern void *func_ov009_0226539c(void *obj);

struct UnkStruct_0221ddbc {
    void *unk_00;
};

struct UnkStruct_0221ddbc_2 {
    void *unk_00;
    char pad_04[0xE8];
    struct UnkStruct_0221ddbc sub;
};

void *func_ov003_0221ddbc(struct UnkStruct_0221ddbc_2 *obj)
{
    struct UnkStruct_0221ddbc *p = &obj->sub;
    obj->unk_00 = data_ov003_02239254;
    p->unk_00 = data_ov003_02239318;
    func_ov009_0226539c(obj);
    return obj;
}
