/* func_0206da80 @ 0x0206da80, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206da80 {
    char *unk_00;
};

extern char data_020df210[];
extern void *func_020a8c38(struct UnkStruct_0206da80 *);

struct UnkStruct_0206da80 *func_0206da80(struct UnkStruct_0206da80 *obj)
{
    obj->unk_00 = data_020df210;
    func_020a8c38(obj);
    return obj;
}
