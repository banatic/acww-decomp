/* func_0207dbe8 @ 0x0207dbe8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void);
extern int func_02003704(void);
extern void func_0207f1c8(void *);
extern void *func_0209b5ec(void);
extern void func_0209c32c(void *, int);
extern void *func_0209bfec(void *);
extern void MI_CpuCopy8(void *, void *, int);
extern void func_0209b5e8(void);
extern void func_0209baf4(void);

void func_0207dbe8(void *p1, void *p2)
{
    void *v;
    void *r;

    func_0208150c();
    if (func_02003704()) {
        func_0207f1c8(p1);
        v = func_0209b5ec();
        func_0209c32c(v, 0xa);
        r = func_0209bfec(v);
        MI_CpuCopy8(p2, r, 8);
        func_0207f1c8(p1);
        func_0209b5e8();
        func_0209baf4();
    }
}
