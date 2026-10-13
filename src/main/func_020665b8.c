/* func_020665b8 @ 0x020665b8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020665f0(void *ptr, int value);
extern void func_02065eac(void *ptr, int value);
extern void func_020666b4(void *ptr);
extern void func_02065d0c(void *p1, void *p2, void *p3, int value);

void func_020665b8(void *arg)
{
    char c;
    char *p;
    func_020665f0(arg, 12);
    func_02065eac(arg, 4);
    func_020666b4((char *) arg + 4);
    c = 0x23;
    p = &c;
    func_02065d0c(p, (char *) arg + 0x44, (char *) arg + 0xf8, 0);
}
