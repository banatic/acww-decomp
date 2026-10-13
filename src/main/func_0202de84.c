/* func_0202de84 @ 0x0202de84, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202de84 {
    void *unk_00;
};
extern void func_0201615c(struct UnkStruct_0202de84 *);
extern unsigned char data_020d9df8[];

struct UnkStruct_0202de84 *func_0202de84(struct UnkStruct_0202de84 *obj)
{
    obj->unk_00 = (void *) data_020d9df8;
    func_0201615c(obj);
    return obj;
}
