/* func_0207ef00 @ 0x0207ef00, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0207ba04(void *a, void *b);
extern void *func_0208150c(void *p);
extern int func_02003704(void *p);
extern void func_02003618(void *a, void *b);

extern unsigned char data_021e5a2c[];

void func_0207ef00(void *a, void *b)
{
    void *p;

    p = func_0207ba04((void *) data_021e5a2c, a);
    if (p != 0 && func_02003704(func_0208150c(p)) != 0) {
        func_02003618(func_0208150c(p), b);
    }
}
