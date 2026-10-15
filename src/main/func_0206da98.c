/* func_0206da98 @ 0x0206da98, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206da98 UnkStruct_0206da98;
struct UnkStruct_0206da98 {
    void *unk_00;
};

extern void *func_020a8cac(UnkStruct_0206da98 *obj);
extern void func_020a8c1c(UnkStruct_0206da98 *obj);
extern char data_020df210;

UnkStruct_0206da98 *func_0206da98(UnkStruct_0206da98 *obj)
{
    func_020a8cac(obj);
    obj->unk_00 = &data_020df210;
    func_020a8c1c(obj);
    return obj;
}
