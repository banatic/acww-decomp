/* func_0207eec4 @ 0x0207eec4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021e5a2c;
extern void *func_0207b9e4(void *table, void *key);
extern void *func_0208150c(void *ptr);
extern int func_02003704(void *ptr);
extern int func_02003618(void *ptr, void *ptr2);

void func_0207eec4(void *p1, void *p2)
{
    void *ret = func_0207b9e4(&data_021e5a2c, p1);
    if (ret != 0 && func_02003704(func_0208150c(ret)) != 0) {
        func_02003618(func_0208150c(ret), p2);
    }
}
