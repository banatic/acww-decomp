/* func_020b191c @ 0x020b191c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b191c {
    unsigned int unk_00;
};

extern void *func_020a8c38(struct UnkStruct_020b191c *obj);
extern void func_020edb3c(struct UnkStruct_020b191c *obj);

extern unsigned char data_020e4290[];

struct UnkStruct_020b191c *func_020b191c(struct UnkStruct_020b191c *obj)
{
    obj->unk_00 = (unsigned int) data_020e4290;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
