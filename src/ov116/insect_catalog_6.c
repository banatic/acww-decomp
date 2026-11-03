/* insect_catalog_6: 3 functions, module ov116
 * mwccarm 1.2/base -O4,s
 * func_ov116_0229e7c0 @ 0x0229e7c0, 0x20 bytes, Thumb
 * func_ov116_0229e7a4 @ 0x0229e7a4, 0x1a bytes, Thumb
 * func_ov116_0229e748 @ 0x0229e748, 0x5c bytes, Thumb
 */

extern void func_ov116_0229e384(void *arg0);
extern void func_ov002_02208090(int, int);
extern unsigned char *func_ov002_022080a0(int, unsigned char value);
extern int func_020ee45c(int a);
extern int func_ov090_0229936c(int a);
extern void func_ov116_0229e36c(int a);
extern int func_ov116_0229ddb8(void *p, int flag);
extern void func_ov114_0229d52c(void *ptr, unsigned int val);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *ptr);
extern void func_ov114_0229d5b8(void *ptr, unsigned int val);
extern void func_ov114_0229cbe4(void *ptr, unsigned int val);
extern void func_ov114_0229d54c(void *ptr);

int func_ov116_0229e7c0(int param)
{
    func_ov116_0229e384((void *) param);
    func_ov002_02208090(param, 0);
    func_ov002_022080a0(param, 1);
    return 1;
}

int func_ov116_0229e7a4(int a)
{
    func_ov090_0229936c(func_020ee45c(a));
    func_ov116_0229e36c(a);
    return 1;
}

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
