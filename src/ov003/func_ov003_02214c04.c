/* func_ov003_02214c04 @ 0x02214c04, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *p);
extern void func_0200e90c(void *p, unsigned char c, int a, int b);
extern int func_0200e894(void *p1, void *p2);
extern void func_0200e91c(void *p);

int func_ov003_02214c04(void *arg0, char arg1, int arg2, int arg3)
{
    char local[28];
    int ret;

    func_0200e92c(local);
    func_0200e90c(local, 0x55, arg2, arg3);
    local[0xc] = arg1;
    ret = func_0200e894(arg0, local);
    func_0200e91c(local);
    return ret;
}
