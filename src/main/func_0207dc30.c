/* func_0207dc30 @ 0x0207dc30, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void);
extern int func_02003704(int);
extern void *func_0207f1c8(void *);
extern void *func_0209b5ec(void *);
extern int func_0209c330(void *);
extern int func_0209c2c0(void *);
extern void func_0209c32c(void *, int);
extern const void *func_0209bfec(void *);
extern void MI_CpuCopy8(const void *, const void *, int);
extern void *func_0209b5e8(void *);
extern void func_0209baf4(void *);

void func_0207dc30(void *a, void *b)
{
    void *p;

    if (func_02003704(func_0208150c()) == 0) {
        return;
    }

    p = func_0209b5ec(func_0207f1c8(a));

    if (func_0209c330(p) == 2 || (func_0209c330(p) == 8 && func_0209c2c0(p) != 0)) {
        ((unsigned char *) p)[0x21] = (unsigned char) ((((unsigned char *) p)[0x21] & ~1) | 1);
    }

    func_0209c32c(p, 9);
    MI_CpuCopy8(b, func_0209bfec(p), 8);
    func_0209baf4(func_0209b5e8(func_0207f1c8(a)));
}
