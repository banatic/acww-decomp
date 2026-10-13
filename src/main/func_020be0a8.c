/* func_020be0a8 @ 0x020be0a8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020be0a8 {
    char pad_00[0x2f24];
    char flag;
};

extern void func_020be000(struct UnkStruct_020be0a8 *obj);
extern void func_020bdb24(struct UnkStruct_020be0a8 *obj);
extern void func_020bd688(struct UnkStruct_020be0a8 *obj);
extern void func_020bd054(struct UnkStruct_020be0a8 *obj);

void func_020be0a8(struct UnkStruct_020be0a8 *obj)
{
    func_020be000(obj);
    func_020bdb24(obj);
    func_020bd688(obj);
    func_020bd054(obj);
    obj->flag = 0;
}
