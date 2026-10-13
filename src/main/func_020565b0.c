/* func_020565b0 @ 0x020565b0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020565b0 {
    void *unk_00;
};

extern char data_020dd154;
extern void func_02057054(struct UnkStruct_020565b0 *obj);

struct UnkStruct_020565b0 *func_020565b0(struct UnkStruct_020565b0 *obj)
{
    obj->unk_00 = &data_020dd154;
    func_02057054(obj);
    return obj;
}
