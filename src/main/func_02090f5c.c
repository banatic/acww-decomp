/* func_02090f5c @ 0x02090f5c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020fa204(unsigned int, void *, void *);
extern void func_02090810(void *);
extern unsigned int data_0213fee4;
struct Vec3 {
    int x;
    int y;
    int z;
};
extern unsigned short func_02090f88(void *p, struct Vec3 v);

struct UnkStruct_02090f5c {
    char pad_00[0x50];
    unsigned int unk_50;
};

int func_02090f5c(struct UnkStruct_02090f5c *param)
{
    func_020fa204(param->unk_50, &data_0213fee4, (void *) func_02090f88);
    func_02090810((char *) param + 0x35c);
    return 1;
}
