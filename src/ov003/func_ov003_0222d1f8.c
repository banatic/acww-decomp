/* func_ov003_0222d1f8 @ 0x0222d1f8, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056578(void *);
extern void func_020edb3c(void *);
extern char data_ov003_0223c0ec;

struct _Obj {
    void *vtbl;
};

void *func_ov003_0222d1f8(struct _Obj *obj)
{
    obj->vtbl = &data_ov003_0223c0ec;
    func_02056578(obj);
    func_020edb3c(obj);
    return obj;
}
