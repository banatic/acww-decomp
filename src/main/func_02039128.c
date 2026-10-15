/* func_02039128 @ 0x02039128, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203a3a4(void *, const void *, int);
extern void func_0203a2f0(void *, const void *, int);
extern void *func_0205195c(void *);
extern int func_020a87e0(void *, void *);
extern int func_02051880(void *, void *);
extern int func_0207762c(void *);
extern void func_0203a2dc(void *);
extern void *func_0203a38c(void *);
extern void MI_CpuCopy8(void *, void *, int);

extern const char data_021c676a[16];
extern const char data_021c675e[6];
extern char data_021c675c;

void *func_02039128(void *a, void *b, void *c)
{
    struct {
        char buf1[16];
        char pad1[8];
        char buf2[6];
        char pad2[10];
    } locals;
    int temp;

    func_0203a3a4(locals.buf1, data_021c676a, 16);
    func_0203a2f0(locals.buf2, data_021c675e, 6);
    func_0205195c(locals.buf1);
    func_0205195c(locals.buf2);
    func_020a87e0(locals.buf1, (char *) c + 0x54);
    func_02051880(locals.buf2, (char *) c + 0x88);
    data_021c675c = 1;
    temp = func_0207762c(b);
    MI_CpuCopy8(&data_021c675c, a, temp);
    func_0203a2dc(locals.buf2);
    return func_0203a38c(locals.buf1);
}
