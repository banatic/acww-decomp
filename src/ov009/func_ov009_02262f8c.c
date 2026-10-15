/* func_ov009_02262f8c @ 0x02262f8c, 0x18 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02262f8c {
    char pad_00[0x40];
    char flag;
};

extern void *func_020f539c(struct UnkStruct_02262f8c *p);

void *func_ov009_02262f8c(struct UnkStruct_02262f8c *obj)
{
    func_020f539c(obj);
    obj->flag = 0;
    return obj;
}
