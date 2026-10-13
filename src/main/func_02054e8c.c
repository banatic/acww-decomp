/* func_02054e8c @ 0x02054e8c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055260(void *);
extern void func_02056f04(void *);
extern char data_020dd0dc;
extern char data_020dd0ec;
extern char data_020dd0fc;

typedef struct {
    void *unk_00;
    char pad_04[152];
    void *unk_9C;
    char pad_A0[24];
    void *unk_B8;
} UnkStruct_02054e8c;

UnkStruct_02054e8c *func_02054e8c(UnkStruct_02054e8c *obj)
{
    func_02055260(obj);
    func_02056f04(&obj->unk_B8);
    obj->unk_00 = (void *) &data_020dd0dc;
    obj->unk_9C = (void *) &data_020dd0ec;
    obj->unk_B8 = (void *) &data_020dd0fc;
    return obj;
}
