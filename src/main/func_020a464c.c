/* func_020a464c @ 0x020a464c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a464c {
    int unk_00;
    int unk_04;
};

extern struct UnkStruct_020a464c *func_020682e0(int a);
extern void func_02068320(struct UnkStruct_020a464c *p, int val);
extern int func_020b5e10(void);
extern void func_020b6098(int a, int b);
extern void func_020a4e94(void *arg, int zero);

void func_020a464c(void *arg)
{
    struct UnkStruct_020a464c *p = func_020682e0(0);
    int val = p->unk_04;
    if (val == 0) {
        func_02068320(p, val);
        func_020b6098(func_020b5e10(), 1);
        func_020a4e94(arg, 0);
    }
}
