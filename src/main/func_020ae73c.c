/* func_020ae73c @ 0x020ae73c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e4170[];
extern void func_020a8c38(void *);
extern void func_020edb3c(void *);

struct UnkStruct_020ae73c {
    void *unk_00;
};

struct UnkStruct_020ae73c *func_020ae73c(struct UnkStruct_020ae73c *obj)
{
    obj->unk_00 = (void *) data_020e4170;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
