/* func_ov116_0229e748 @ 0x0229e748, 0x5c bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov116_0229ddb8(void *p, int flag);
extern void func_ov114_0229d52c(void *ptr, unsigned int val);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *ptr);
extern void func_ov114_0229d5b8(void *ptr, unsigned int val);
extern void func_ov114_0229cbe4(void *ptr, unsigned int val);
extern void func_ov114_0229d54c(void *ptr);

int func_ov116_0229e748(unsigned char *self)
{
    if (func_ov116_0229ddb8(self, 1) == 0) {
        return 1;
    }
    func_ov114_0229d52c(self + 0xf8, *(unsigned int *) (self + 0x1424));
    if (func_0206fe54()) {
        func_ov002_02209eb8(self + 0x94);
    }
    func_ov114_0229d5b8(self + 0xf8, *(unsigned int *) (self + 0x1424));
    func_ov114_0229cbe4(self + 0xf8, *(unsigned int *) (self + 0x1424));
    func_ov114_0229d54c(self + 0xf8);
    return 1;
}
