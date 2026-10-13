/* func_020f5400 @ 0x020f5400, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f5400 {
    void *volatile unk_00;
};

extern void func_020f5914(struct UnkStruct_020f5400 *obj);

extern unsigned char data_020d8414[];
extern unsigned char data_0213f058[];

void *func_020f5400(struct UnkStruct_020f5400 *obj)
{
    obj->unk_00 = (void *) data_0213f058;
    obj->unk_00 = (void *) data_020d8414;
    func_020f5914(obj);
    return obj;
}
