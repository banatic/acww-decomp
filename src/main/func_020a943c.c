/* func_020a943c @ 0x020a943c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e3e24;

struct UnkStruct_020a943c {
    void *unk_00;
    char unk_04[4];
    char unk_08[4];
};

extern void func_020a94a4(struct UnkStruct_020a943c *obj);
extern void func_020a9c98(void *self);
extern void func_020edb3c(struct UnkStruct_020a943c *obj);

struct UnkStruct_020a943c *func_020a943c(struct UnkStruct_020a943c *obj)
{
    obj->unk_00 = &data_020e3e24;
    func_020a94a4(obj);
    func_020a9c98(obj->unk_08);
    func_020edb3c(obj);
    return obj;
}
