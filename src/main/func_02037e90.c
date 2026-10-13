/* func_02037e90 @ 0x02037e90, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020e9968(int, int, int);
extern void func_02037f5c(void *);

void *func_02037e90(int count, int arg2, int arg3)
{
    char *base = func_020e9968(arg2, count * 40, arg3);
    int i;

    if (base) {
        for (i = 0; i < count; i++) {
            if (base + i * 40) {
                func_02037f5c(base + i * 40);
            }
        }
    }
    return base;
}