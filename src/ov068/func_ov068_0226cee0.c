/* func_ov068_0226cee0 @ 0x0226cee0, 0x78 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0226d4ac(void *p);
extern void *func_ov068_0226cf58(void *p);
extern void *func_02014868(void *p);
extern void func_02079410(void *obj, void *value);
extern void func_ov068_0226cd34(void *dst, void *src);
extern void func_ov068_02266e98(void *dst, void *src);
extern void func_0201c6d0(void *dst, void *src);
extern void func_ov068_0226687c(void *dst, void *src);

int func_ov068_0226cee0(char *p)
{
    void *obj;
    void *tmp;

    func_ov068_0226d4ac(p);
    obj = func_ov068_0226cf58(p);
    if (obj != 0) {
        tmp = func_02014868(p + 0x618);
        func_02079410(obj, tmp);
    }
    func_ov068_0226cd34(p + 0x8b8, p);
    func_ov068_02266e98(p + 0x9f4, p);
    func_0201c6d0(p + 0x83c, p);
    func_ov068_0226687c(p + 0x898, p);
    p[0xa05] = 0;
    return 1;
}
