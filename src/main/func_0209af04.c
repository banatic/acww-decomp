/* func_0209af04 @ 0x0209af04, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd5c(void *);
extern void func_02003738(void *);
extern void MI_CpuFill8(void *, int, int);

void func_0209af04(void *arg0)
{
    void *p;
    int i;

    p = arg0;
    func_0209bd5c((char *) p + 0x10);
    func_02003738(p);
    i = 0;
    *(int *) ((char *) p + 0x1c) = i;
    *(int *) ((char *) p + 0x20) = i;
    MI_CpuFill8((char *) p + 0x24, 0, 1);
}
