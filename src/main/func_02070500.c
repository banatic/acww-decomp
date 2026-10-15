/* func_02070500 @ 0x02070500, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020e9958(void *, unsigned int);
extern void MI_CpuCopy8(unsigned char *, const void *, unsigned int);
extern int func_020979f0(const void *, int);
extern int func_0209782c(void);
extern void func_020e993c(void *, const void *);
extern void func_0207055c(int, int);
extern void *data_021fbe94;

void func_02070500(unsigned char *p, int q)
{
    void *heap;
    void *r;
    int err;

    heap = data_021fbe94;
    r = func_020e9958(heap, 0x100);
    err = 11;
    MI_CpuCopy8(p + 1, r, 0x100);
    if (func_020979f0(r, 1) != 0) {
        if (func_0209782c() != 0) {
            err = 9;
        } else {
            err = 10;
        }
    }
    func_020e993c(heap, r);
    func_0207055c(err, q);
}
