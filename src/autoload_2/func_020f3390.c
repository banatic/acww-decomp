/* func_020f3390 @ 0x020f3390, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f45c4(void *p);
extern unsigned char data_0213ebd8;

struct UnkStruct_020f3390 {
    void *unk_00;
    unsigned char unk_04;
};

struct UnkStruct_020f3390 *func_020f3390(struct UnkStruct_020f3390 *obj)
{
    func_020f45c4(obj);
    obj->unk_00 = &data_0213ebd8;
    obj->unk_04 = 0x20;
    return obj;
}
