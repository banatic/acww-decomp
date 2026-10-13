/* func_02085d2c @ 0x02085d2c, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *p);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned n);
extern int func_0203fc78(void *self, void *dst, int flag);

struct Pair {
    int a;
    int b;
};

int func_02085d2c(void *self, const struct Pair *src)
{
    struct Pair local;
    struct Pair dst;
    local.a = 0;
    local.b = 0;
    if (src == 0) {
        func_0209e474(&local);
        src = &local;
    }
    MI_CpuCopy8(src, &dst, 8);
    if (func_0203fc78(self, &dst, 0) != 0) {
        return 1;
    } else {
        return 0;
    }
}
