/* func_020f539c @ 0x020f539c, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f539c {
    int *ptr;
    char pad_04[0x3a];
    unsigned char flag;
};

extern int data_0213f090;
extern void func_020f5970(struct UnkStruct_020f539c *);

struct UnkStruct_020f539c *func_020f539c(struct UnkStruct_020f539c *obj)
{
    func_020f5970(obj);
    obj->ptr = &data_0213f090;
    obj->flag = 2;
    return obj;
}
