/* func_020f2b2c @ 0x020f2b2c, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f45c4(void *);
extern char data_0213ede0;

struct UnkStruct_020f2b2c {
    void *unk_00;
    unsigned char unk_04;
};

void *func_020f2b2c(struct UnkStruct_020f2b2c *obj)
{
    func_020f45c4(obj);
    obj->unk_00 = &data_0213ede0;
    obj->unk_04 = 0x2e;
    return obj;
}
