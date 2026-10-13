/* func_ov096_0229e29c @ 0x0229e29c, 0x2c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229e29c {
    unsigned char pad_00[0xc0];
    unsigned char flag;
};

extern void func_ov096_0229fb9c(struct UnkStruct_0229e29c *);
extern void func_ov096_0229e82c(struct UnkStruct_0229e29c *, int);
extern void func_ov096_0229f874(struct UnkStruct_0229e29c *, int, int, int);

void func_ov096_0229e29c(struct UnkStruct_0229e29c *obj)
{
    func_ov096_0229fb9c(obj);
    func_ov096_0229e82c(obj, 1);
    if (obj->flag == 0) {
        func_ov096_0229f874(obj, 7, 0xff, 1);
    }
}
