/* func_ov004_02239f9c @ 0x02239f9c, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223a374(void *);
extern void func_020edb3c(void *);
extern char data_ov004_02255dcc;

struct _Obj {
    void *vtbl;
};

void *func_ov004_02239f9c(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02255dcc;
    func_ov004_0223a374(obj);
    func_020edb3c(obj);
    return obj;
}
