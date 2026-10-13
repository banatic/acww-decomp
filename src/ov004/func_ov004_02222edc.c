/* func_ov004_02222edc @ 0x02222edc, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *);
extern void func_020edb3c(void *);
extern char data_ov004_022543cc;

struct _Obj {
    void *vtbl;
};

void *func_ov004_02222edc(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_022543cc;
    func_0202eb20(obj);
    func_020edb3c(obj);
    return obj;
}
