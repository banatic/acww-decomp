/* villager_names: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207ef00 @ 0x0207ef00, 0x3c bytes, Thumb
 * func_0207eec4 @ 0x0207eec4, 0x3c bytes, Thumb
 * func_0207ee78 @ 0x0207ee78, 0x4c bytes, Thumb
 */

extern void *func_0207ba04(void *a, void *b);
extern void *func_0208150c(void *p);
extern int func_02003704(void *p);
extern int func_02003618(void *a, void *b);
extern unsigned char data_021e5a2c[];
extern void *func_0207b9e4(void *table, void *key);
extern char *func_02137550(void *, unsigned int);
extern int func_0207cc94(const void *, int *, int);

void func_0207ef00(void *a, void *b)
{
    void *p;

    p = func_0207ba04((void *) data_021e5a2c, a);
    if (p != 0 && func_02003704(func_0208150c(p)) != 0) {
        func_02003618(func_0208150c(p), b);
    }
}

void func_0207eec4(void *p1, void *p2)
{
    void *ret = func_0207b9e4(((char *) data_021e5a2c), p1);
    if (ret != 0 && func_02003704(func_0208150c(ret)) != 0) {
        func_02003618(func_0208150c(ret), p2);
    }
}

void func_0207ee78(int a, int b)
{
    int local;
    int tmp;

    func_02137550(&local, 4);
    local = (int) func_0208150c((void *) a);
    tmp = func_0207cc94((const void *) data_021e5a2c, &local, 1);
    if (tmp != 0) {
        if (func_02003704((void *) ((int) func_0208150c((void *) tmp))) != 0) {
            func_02003618((void *) ((int) func_0208150c((void *) tmp)), (void *) b);
        }
    }
}
