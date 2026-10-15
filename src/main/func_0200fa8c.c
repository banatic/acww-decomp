/* func_0200fa8c @ 0x0200fa8c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200fa6c(void *, int);
extern void func_0204f7e0(void *, void *);

void func_0200fa8c(void *param, int argument1)
{
    void *sp[4];
    func_0200fa6c(sp, (int) argument1);
    func_0204f7e0(param, sp);
}
