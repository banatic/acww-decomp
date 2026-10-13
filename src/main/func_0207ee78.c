/* func_0207ee78 @ 0x0207ee78, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02137550(void *, unsigned int);
extern int func_0208150c(int);
extern int func_0207cc94(const void *, int *, int);
extern int func_02003704(int);
extern void func_02003618(int, int);

extern unsigned char data_021e5a2c[];

void func_0207ee78(int a, int b)
{
    int local;
    int tmp;

    func_02137550(&local, 4);
    local = func_0208150c(a);
    tmp = func_0207cc94((const void *) data_021e5a2c, &local, 1);
    if (tmp != 0) {
        if (func_02003704(func_0208150c(tmp)) != 0) {
            func_02003618(func_0208150c(tmp), b);
        }
    }
}
