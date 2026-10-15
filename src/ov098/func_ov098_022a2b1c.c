/* func_ov098_022a2b1c @ 0x022a2b1c, 0x50 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a2b1c {
    char pad_00[0xC4];
    int unk_C4;
};

extern int func_020436a8(int);
extern unsigned char *func_ov002_02208098(struct UnkStruct_022a2b1c *, unsigned char value);
extern void func_ov098_022a2ac8(struct UnkStruct_022a2b1c *);
extern void func_ov096_0229fb9c(struct UnkStruct_022a2b1c *);
extern void func_ov096_0229f874(struct UnkStruct_022a2b1c *, int, int, int);
extern void func_020431b8(int);

void func_ov098_022a2b1c(struct UnkStruct_022a2b1c *arg)
{
    int ret = func_020436a8(arg->unk_C4);
    switch (ret) {
        case 1:
            func_ov002_02208098(arg, 0x2E);
            func_ov098_022a2ac8(arg);
            break;
        case 2:
            func_ov096_0229fb9c(arg);
            func_ov096_0229f874(arg, 3, 0xFF, 1);
            break;
        default:
            return;
    }
    func_020431b8(arg->unk_C4);
    arg->unk_C4 = -1;
}
