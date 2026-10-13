/* func_02065c78 @ 0x02065c78, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020de770;

struct UnkStruct_02065c78 {
    void *unk_00;
};

extern void func_020a887c(struct UnkStruct_02065c78 *obj);
extern void func_020edb3c(struct UnkStruct_02065c78 *obj);

struct UnkStruct_02065c78 *func_02065c78(struct UnkStruct_02065c78 *obj)
{
    obj->unk_00 = &data_020de770;
    func_020a887c(obj);
    func_020edb3c(obj);
    return obj;
}
