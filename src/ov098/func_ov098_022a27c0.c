/* func_ov098_022a27c0 @ 0x022a27c0, 0x30 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b74c(void *p);
extern void func_ov002_0220b738(void *p);
extern void func_ov096_0229fb9c(void *p);
extern int func_020960f8(int, int);

struct UnkStruct_022a27c0 {
    char pad_00[0x2958];
    char arr[1];
};

void func_ov098_022a27c0(struct UnkStruct_022a27c0 *arg)
{
    func_ov002_0220b74c((void *) &arg->arr);
    if (func_020960f8(6, 4) == 0) {
        func_ov002_0220b738((void *) arg->arr);
        func_ov096_0229fb9c((void *) arg);
    }
}
