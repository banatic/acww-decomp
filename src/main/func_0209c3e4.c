/* func_0209c3e4 @ 0x0209c3e4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209c53c(void *ptr);
extern void func_0209c398(void *ptr);

void *func_0209c3e4(void *obj)
{
    int *p = (int *) obj;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    func_0209c53c((char *) obj + 0x11);
    func_0209c53c((char *) obj + 0x19);
    func_0209c398(obj);
    return obj;
}
