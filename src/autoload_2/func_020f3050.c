/* func_020f3050 @ 0x020f3050, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f3050 {
    void *vptr;
    char unk_04;
};

extern void *func_020f45c4(struct UnkStruct_020f3050 *);
extern char data_0213eca8;

struct UnkStruct_020f3050 *func_020f3050(struct UnkStruct_020f3050 *obj)
{
    func_020f45c4(obj);
    obj->vptr = &data_0213eca8;
    obj->unk_04 = 0x28;
    return obj;
}
