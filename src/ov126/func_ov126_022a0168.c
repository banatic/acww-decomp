/* func_ov126_022a0168 @ 0x022a0168, 0x74 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov124_0229f2dc(void *, void *, unsigned char);
extern int func_ov126_0229f7c8(void *, int);
extern int func_02051d08(void *, unsigned char);
extern void func_ov124_0229f320(void *);
extern void func_ov126_022a011c(void *);
extern void func_ov124_0229f2e4(void *);
extern void func_ov126_0229f7b8(void *, int);
extern void func_ov126_022a0978(void *);

void func_ov126_022a0168(void *self)
{
    char *base = (char *) self;
    func_ov124_0229f2dc(base + 0xb0, base + 0x4248, *((unsigned char *) (base + 0xa6)));
    if (func_ov126_0229f7c8(base, 0x100) != 0) {
        int r = func_02051d08(base + 0x4248, *((unsigned char *) (base + 0xa6)));
        *(int *) (base + 0xa0) = -(*((unsigned char *) (base + 0xaf)) - r - 2);
    }
    func_ov124_0229f320(base + 0xb0);
    func_ov126_022a011c(base);
    func_ov124_0229f2e4(base + 0xb0);
    func_ov126_0229f7b8(base, 0x10);
    func_ov126_022a0978(base);
}
