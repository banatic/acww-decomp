/* func_020a682c @ 0x020a682c, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a6878(void *p);
extern void func_020a7704(void *p, int *b, int *a);
extern void *MI_CpuCopy8(void *dst, const void *src, int n);
extern void func_020a76f8(void *p);

void func_020a682c(void *param)
{
    int a, b;
    char *p;
    int i;

    if (func_020a6878(param) < 4) {
        p = (char *) param + 12;
        for (i = 2; i >= 0; i--) {
            char *q = p + 8;
            func_020a7704(q, &b, &a);
            if (b < 4) {
                MI_CpuCopy8(q, p, 8);
                p += 8;
            } else {
                break;
            }
        }
        func_020a76f8(p);
    }
}
