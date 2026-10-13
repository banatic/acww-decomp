/* func_020f31e8 @ 0x020f31e8, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *);
extern int data_0213e9d0;

struct UnkStruct_020f31e8 {
    int *unk_00;
    unsigned char unk_04;
};

struct UnkStruct_020f31e8 *func_020f31e8(struct UnkStruct_020f31e8 *obj)
{
    func_020f45c4(obj);
    obj->unk_00 = &data_0213e9d0;
    obj->unk_04 = 0x22;
    return obj;
}
