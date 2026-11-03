/* menu_tab_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208c020 @ 0x0208c020, 0x2a bytes, Thumb
 * func_0208c008 @ 0x0208c008, 0x18 bytes, Thumb
 */

extern void func_0208be3c(void *param);
extern void func_0208c688(void *param);
extern void func_0208c668(void *ptr);
extern void *func_0208a144(void *ptr);

void func_0208c020(void *param)
{
    unsigned char *p = (unsigned char *) param;
    p[0x26] = 0;
    p[0x24] = 0;
    p[0x25] = 0;
    func_0208be3c(param);
    func_0208c688((void *) ((unsigned char *) param + 0x28));
}

void func_0208c008(void *arg)
{
    void *r4;
    r4 = arg;
    func_0208c668((char *) r4 + 0x28);
    func_0208a144((char *) r4 + 0xc);
}
