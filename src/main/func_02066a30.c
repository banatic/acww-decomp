/* func_02066a30 @ 0x02066a30, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a81b8(void *obj);
extern void func_02066a9c(void *sub);
extern char data_020df008;

struct UnkStruct_02066a30 {
    void *unk_00;
    char pad_04[0x1c];
    char sub[0x20];
    int unk_40;
    char unk_44;
};

struct UnkStruct_02066a30 *func_02066a30(struct UnkStruct_02066a30 *obj)
{
    func_020a81b8(obj);
    obj->unk_00 = &data_020df008;
    func_02066a9c(obj->sub);
    obj->unk_40 = 0;
    *((char *) obj + 0x44) = 0;
    return obj;
}
