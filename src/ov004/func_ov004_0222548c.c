/* func_ov004_0222548c @ 0x0222548c, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0201615c(void *);
extern void func_020edb3c(void *);
extern char data_ov004_02254888;

struct _Obj {
    void *vtbl;
};

void *func_ov004_0222548c(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_02254888;
    func_0201615c(obj);
    func_020edb3c(obj);
    return obj;
}
