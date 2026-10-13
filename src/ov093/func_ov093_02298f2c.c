/* func_ov093_02298f2c @ 0x02298f2c, 0x20 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov093_022998b8;

struct UnkStruct_02298f2c {
    void *vtable;
};

extern void func_020a8c38(struct UnkStruct_02298f2c *p, void *q);
extern void func_020edb3c(struct UnkStruct_02298f2c *p);

struct UnkStruct_02298f2c *func_ov093_02298f2c(struct UnkStruct_02298f2c *p)
{
    p->vtable = &data_ov093_022998b8;
    func_020a8c38(p, &data_ov093_022998b8);
    func_020edb3c(p);
    return p;
}
