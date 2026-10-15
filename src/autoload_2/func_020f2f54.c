/* func_020f2f54 @ 0x020f2f54, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213ecdc;
extern void *func_020f95f8(void *sub);
extern void *func_020f4514(void *obj);

struct UnkStruct_020f2f54 {
    void *unk_00;
    int pad_04;
};

struct UnkStruct_020f2f54 *func_020f2f54(struct UnkStruct_020f2f54 *obj)
{
    obj->unk_00 = &data_0213ecdc;
    func_020f95f8((char *) obj + 8);
    func_020f4514(obj);
    return obj;
}
