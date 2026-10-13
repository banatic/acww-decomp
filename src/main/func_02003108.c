/* func_02003108 @ 0x02003108, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ff20;
extern void func_02003100(int *p);
extern int func_020030dc(int *p);
extern int func_020030bc(int *p);
extern void func_02003064(int *p);
extern void func_02003038(int *p);
extern void func_020030a4(int *p);
extern void func_0200308c(int *p);

void func_02003108(void)
{
    int *p = &data_0213ff20;
    int r4, r5;

    func_02003100(p);
    r4 = func_020030dc(p);
    r5 = func_020030bc(p);
    if (r4 != 0) {
        func_02003064(p);
    }
    if (r5 != 0) {
        func_02003038(p);
    }
    func_020030a4(p);
    func_0200308c(p);
}
