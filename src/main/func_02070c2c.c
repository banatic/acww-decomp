/* func_02070c2c @ 0x02070c2c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02070c2c UnkStruct_02070c2c;
struct UnkStruct_02070c2c {
    void *unk_00;
    char pad_04[0x64];
    int unk_68;
};

extern void func_020a8cac(UnkStruct_02070c2c *obj);
extern void func_020a8c1c(UnkStruct_02070c2c *obj);
extern char data_020e179c;

UnkStruct_02070c2c *func_02070c2c(UnkStruct_02070c2c *obj)
{
    func_020a8cac(obj);
    obj->unk_00 = &data_020e179c;
    func_020a8c1c(obj);
    obj->unk_68 = 0;
    return obj;
}
