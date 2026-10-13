/* func_020754b0 @ 0x020754b0, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void *);
extern void *func_020a132c(void *);
extern void *func_020a1250(void *);
extern void func_020a1254(void *, int);
extern void *MI_CpuCopy8(void *, const void *, unsigned int);

void func_020754b0(void *arg)
{
    int v;
    void *p;

    v = func_020b65c4(arg);
    if (v != 12) {
        return;
    }

    p = func_020a132c((void *) v);
    if (p == 0) {
        return;
    }

    func_020a1254(func_020a132c(MI_CpuCopy8(arg, func_020a1250(func_020a132c(p)), 8)), 1);
}
