/* func_0207bf38 @ 0x0207bf38, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208150c(void *p);
extern int func_02003704(void *p);
extern void func_0207d978(void *p, void *arg);
extern void func_0207d91c(void *p, void *arg);
extern int func_0207d788(void *p, void *a, void *b, void *arg);
extern unsigned int func_0207f1c8(void *p);
extern int func_0209b5e8(int);
extern void func_0209baf4(void *);

void func_0207bf38(char *base, void *arg)
{
    char *p;
    int i;

    p = base;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p)) != 0) {
            func_0207d978(p, arg);
            func_0207d91c(p, arg);
            if (func_0207d788(p, base + 0x4050, base + 0x4058, arg) != 0xc) {
                func_0209baf4((void *) func_0209b5e8((int) func_0207f1c8(p)));
            }
        }
        p += 0x7ec;
    }
}
