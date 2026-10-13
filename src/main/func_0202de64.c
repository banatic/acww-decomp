/* func_0202de64 @ 0x0202de64, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202de64 {
    void *unk_00;
};

extern char data_020d9df8[];
void func_0201615c(struct UnkStruct_0202de64 *obj);
void func_020edb3c(struct UnkStruct_0202de64 *obj);

struct UnkStruct_0202de64 *func_0202de64(struct UnkStruct_0202de64 *obj)
{
    obj->unk_00 = data_020d9df8;
    func_0201615c(obj);
    func_020edb3c(obj);
    return obj;
}
