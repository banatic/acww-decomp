/* func_02085be0 @ 0x02085be0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034270(void *obj, int a, int b, int c);
extern int func_0207f1d8(int a);
extern int func_020341c8(void *obj, int a);
extern unsigned char *func_020800d0(int a);
extern void func_0204f794(int a, int b, int c);
extern void func_0203423c(void *obj);

void func_02085be0(int param1, int param2)
{
    unsigned char obj[0x44];
    unsigned char *p;

    func_02034270(obj, param2, 0, 0);
    if (func_0207f1d8(param1) == 0 && func_020341c8(obj, 0) != 0) {
        p = func_020800d0(param1);
        func_0204f794(param2, p[0] + 1, p[1] + 2);
    }
    func_0203423c(obj);
}
